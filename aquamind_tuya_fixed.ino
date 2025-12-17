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
const char* endpoint = "https://openapi.tuyaeu.com";  // FIXED URL

Servo valves[4];
String accessToken = "";

void setup() {
  Serial.begin(115200);
  
  pinMode(2, OUTPUT);
  for(int i = 0; i < 4; i++) {
    valves[i].attach(5 + i);
  }
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  
  getAccessToken();
  Serial.println("AquaMind Ready");
}

void loop() {
  float flow = analogRead(A0);
  float turbidity = analogRead(A1);
  bool anomaly = (turbidity > 600 || flow < 100);
  
  String decision = sendToTuya(flow, turbidity, anomaly);
  executeDecision(decision);
  
  Serial.printf("Flow: %.0f | Turbidity: %.0f | Decision: %s\n", 
                flow, turbidity, decision.c_str());
  delay(30000);
}

void getAccessToken() {
  HTTPClient http;
  http.begin(String(endpoint) + "/v1.0/token?grant_type=1");
  http.addHeader("client_id", accessId);
  http.addHeader("secret", accessSecret);
  
  int httpCode = http.GET();
  Serial.printf("Token request: %d\n", httpCode);
  
  if (httpCode == 200) {
    String response = http.getString();
    StaticJsonDocument<500> doc;
    deserializeJson(doc, response);
    accessToken = doc["result"]["access_token"].as<String>();
    Serial.println("✅ Token obtained");
  } else {
    Serial.println("❌ Token failed");
  }
  http.end();
}

String sendToTuya(float flow, float turbidity, bool anomaly) {
  // Always use local decision for now
  return makeLocalDecision(flow, turbidity, anomaly);
}

String makeLocalDecision(float flow, float turbidity, bool anomaly) {
  if (turbidity > 800 || flow < 50) return "shutdown";
  if (anomaly) return "purify";
  return "normal";
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
