#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include <mbedtls/md.h>

// WiFi credentials - UPDATE THESE
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Real Tuya credentials
const char* accessId = "mraudgsm5fs77tj8wmyf";
const char* accessSecret = "4733aa38304f4ac5b235ae3984c137f9";
const char* endpoint = "https://openapi.tuyaeu.com";

// TTGO ESP32 pins
#define FLOW_PIN 36      // ADC1_CH0
#define TURBIDITY_PIN 39 // ADC1_CH3
#define PUMP_LED 2       // Built-in LED
#define VALVE_LED_1 4
#define VALVE_LED_2 16
#define VALVE_LED_3 17
#define VALVE_LED_4 5

String accessToken = "";
unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);
  
  // Initialize pins
  pinMode(PUMP_LED, OUTPUT);
  pinMode(VALVE_LED_1, OUTPUT);
  pinMode(VALVE_LED_2, OUTPUT);
  pinMode(VALVE_LED_3, OUTPUT);
  pinMode(VALVE_LED_4, OUTPUT);
  
  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected");
  Serial.println("IP: " + WiFi.localIP().toString());
  
  // Initialize time for Tuya API
  configTime(0, 0, "pool.ntp.org");
  
  // Get Tuya access token
  getTuyaToken();
  
  Serial.println("🌊 AquaMind TTGO Real Test Ready");
  Serial.println("Touch sensors or use potentiometers on pins 36,39");
}

void loop() {
  // Read real sensor values
  int flowRaw = analogRead(FLOW_PIN);
  int turbidityRaw = analogRead(TURBIDITY_PIN);
  
  // Convert to meaningful values (0-1000)
  float flow = map(flowRaw, 0, 4095, 0, 1000);
  float turbidity = map(turbidityRaw, 0, 4095, 0, 1000);
  
  // Make local decision
  String decision = makeLocalDecision(flow, turbidity);
  
  // Send to Tuya Cloud every 30 seconds
  if (millis() - lastSend > 30000) {
    sendToTuyaCloud(flow, turbidity, decision);
    lastSend = millis();
  }
  
  // Execute decision
  executeDecision(decision);
  
  // Print status
  Serial.printf("Flow: %3.0f | Turbidity: %3.0f | Decision: %s\n", 
                flow, turbidity, decision.c_str());
  
  delay(2000);
}

void getTuyaToken() {
  HTTPClient http;
  http.begin(String(endpoint) + "/v1.0/token?grant_type=1");
  
  // Add timestamp
  time_t now = time(nullptr);
  String timestamp = String(now * 1000);
  
  http.addHeader("client_id", accessId);
  http.addHeader("secret", accessSecret);
  http.addHeader("t", timestamp);
  
  int httpCode = http.GET();
  Serial.printf("Token request: %d\n", httpCode);
  
  if (httpCode == 200) {
    String response = http.getString();
    Serial.println("Response: " + response);
    
    StaticJsonDocument<1000> doc;
    deserializeJson(doc, response);
    
    if (doc["success"]) {
      accessToken = doc["result"]["access_token"].as<String>();
      Serial.println("✅ Tuya token obtained");
    } else {
      Serial.println("❌ Token failed: " + doc["msg"].as<String>());
    }
  } else {
    Serial.println("❌ HTTP error: " + String(httpCode));
  }
  http.end();
}

void sendToTuyaCloud(float flow, float turbidity, String decision) {
  if (accessToken == "") {
    Serial.println("⚠️ No token, using local decision");
    return;
  }
  
  HTTPClient http;
  http.begin(String(endpoint) + "/v1.0/iot-03/devices/commands");
  
  time_t now = time(nullptr);
  String timestamp = String(now * 1000);
  
  http.addHeader("Content-Type", "application/json");
  http.addHeader("client_id", accessId);
  http.addHeader("access_token", accessToken);
  http.addHeader("t", timestamp);
  
  StaticJsonDocument<300> doc;
  doc["device_id"] = "aquamind_ttgo_001";
  doc["commands"][0]["code"] = "flow";
  doc["commands"][0]["value"] = flow;
  doc["commands"][1]["code"] = "turbidity";
  doc["commands"][1]["value"] = turbidity;
  doc["commands"][2]["code"] = "decision";
  doc["commands"][2]["value"] = decision;
  
  String payload;
  serializeJson(doc, payload);
  
  int httpCode = http.POST(payload);
  Serial.printf("☁️ Tuya send: %d\n", httpCode);
  
  if (httpCode == 200) {
    String response = http.getString();
    Serial.println("Tuya response: " + response);
  }
  
  http.end();
}

String makeLocalDecision(float flow, float turbidity) {
  bool anomaly = (turbidity > 600 || flow < 100);
  
  if (turbidity > 800 || flow < 50) {
    return "shutdown";
  } else if (anomaly) {
    return "purify";
  } else {
    return "normal";
  }
}

void executeDecision(String decision) {
  if (decision == "shutdown") {
    // Emergency: All off
    digitalWrite(PUMP_LED, LOW);
    digitalWrite(VALVE_LED_1, LOW);
    digitalWrite(VALVE_LED_2, LOW);
    digitalWrite(VALVE_LED_3, LOW);
    digitalWrite(VALVE_LED_4, LOW);
    Serial.println("🔴 EMERGENCY: All systems OFF");
    
  } else if (decision == "purify") {
    // Purify: Pump on, close contaminated valve
    digitalWrite(PUMP_LED, HIGH);
    digitalWrite(VALVE_LED_1, LOW);  // Close contaminated
    digitalWrite(VALVE_LED_2, HIGH);
    digitalWrite(VALVE_LED_3, HIGH);
    digitalWrite(VALVE_LED_4, HIGH);
    Serial.println("🟡 PURIFY: Contaminated line isolated");
    
  } else {
    // Normal: All on
    digitalWrite(PUMP_LED, HIGH);
    digitalWrite(VALVE_LED_1, HIGH);
    digitalWrite(VALVE_LED_2, HIGH);
    digitalWrite(VALVE_LED_3, HIGH);
    digitalWrite(VALVE_LED_4, HIGH);
    Serial.println("🟢 NORMAL: All systems operational");
  }
}
