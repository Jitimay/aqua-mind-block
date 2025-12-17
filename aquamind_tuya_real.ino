#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

// WiFi credentials - UPDATE THESE
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Real Tuya credentials
const char* accessId = "mraudgsm5fs77tj8wmyf";
const char* accessSecret = "4733aa38304f4ac5b235ae3984c137f9";
const char* projectCode = "p1765985685343j83nve";
const char* endpoint = "https://openapi-weeu.tuyaeu.com";

Servo valves[4];
String accessToken = "";

void setup() {
  Serial.begin(115200);
  
  // Initialize hardware
  pinMode(2, OUTPUT); // Pump relay
  for(int i = 0; i < 4; i++) {
    valves[i].attach(5 + i);
  }
  
  // Connect WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  
  // Get Tuya access token
  getAccessToken();
  
  Serial.println("AquaMind Blocks Ready with Tuya Integration");
}

void loop() {
  float flow = analogRead(A0);
  float turbidity = analogRead(A1);
  bool anomaly = (turbidity > 600 || flow < 100);
  
  // Send to Tuya Cloud
  String decision = sendToTuya(flow, turbidity, anomaly);
  
  // Execute decision
  executeDecision(decision);
  
  Serial.printf("Flow: %.0f | Turbidity: %.0f | Decision: %s\n", 
                flow, turbidity, decision.c_str());
  
  delay(30000);
}

void getAccessToken() {
  HTTPClient http;
  http.begin(String(endpoint) + "/v1.0/token?grant_type=1");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("client_id", accessId);
  http.addHeader("secret", accessSecret);
  
  int httpCode = http.GET();
  if (httpCode == 200) {
    String response = http.getString();
    StaticJsonDocument<500> doc;
    deserializeJson(doc, response);
    accessToken = doc["result"]["access_token"].as<String>();
    Serial.println("✅ Tuya token obtained");
  } else {
    Serial.println("❌ Failed to get Tuya token");
  }
  http.end();
}

String sendToTuya(float flow, float turbidity, bool anomaly) {
  if (accessToken == "") return makeLocalDecision(flow, turbidity, anomaly);
  
  HTTPClient http;
  http.begin(String(endpoint) + "/v1.0/iot-03/devices/data");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("client_id", accessId);
  http.addHeader("access_token", accessToken);
  
  StaticJsonDocument<300> doc;
  doc["device_id"] = "aquamind_001";
  doc["flow"] = flow;
  doc["turbidity"] = turbidity;
  doc["anomaly"] = anomaly;
  doc["timestamp"] = millis();
  
  String payload;
  serializeJson(doc, payload);
  
  int httpCode = http.POST(payload);
  String decision = "normal";
  
  if (httpCode == 200) {
    String response = http.getString();
    StaticJsonDocument<200> responseDoc;
    deserializeJson(responseDoc, response);
    decision = responseDoc["decision"] | makeLocalDecision(flow, turbidity, anomaly);
    Serial.println("☁️ Tuya Cloud decision received");
  } else {
    decision = makeLocalDecision(flow, turbidity, anomaly);
    Serial.println("🔄 Using local AI decision");
  }
  
  http.end();
  return decision;
}

String makeLocalDecision(float flow, float turbidity, bool anomaly) {
  if (turbidity > 800 || flow < 50) {
    return "shutdown";
  } else if (anomaly) {
    return "purify";
  } else {
    return "normal";
  }
}

void executeDecision(String decision) {
  if(decision == "shutdown") {
    digitalWrite(2, LOW);
    for(int i = 0; i < 4; i++) valves[i].write(0);
  } else if(decision == "purify") {
    digitalWrite(2, HIGH);
    valves[0].write(0);
    for(int i = 1; i < 4; i++) valves[i].write(90);
  } else {
    digitalWrite(2, HIGH);
    for(int i = 0; i < 4; i++) valves[i].write(90);
  }
}
