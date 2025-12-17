#include <WiFi.h>
#include <ESP32Servo.h>

// Credentials - YOU PROVIDE THESE
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

Servo valves[4];

struct SensorData {
  float flow;
  float turbidity;
  bool anomaly;
};

void setup() {
  Serial.begin(115200);
  
  // Initialize hardware
  pinMode(2, OUTPUT); // Pump relay
  for(int i = 0; i < 4; i++) {
    valves[i].attach(5 + i);
  }
  
  // Connect WiFi (optional for standalone)
  WiFi.begin(ssid, password);
  
  Serial.println("AquaMind Blocks Ready (Standalone Mode)");
}

void loop() {
  SensorData data = readSensors();
  String decision = makeLocalDecision(data);
  executeDecision(decision);
  
  printStatus(data, decision);
  delay(5000);
}

SensorData readSensors() {
  SensorData data;
  data.flow = analogRead(A0);
  data.turbidity = analogRead(A1);
  data.anomaly = (data.turbidity > 600 || data.flow < 100);
  return data;
}

String makeLocalDecision(SensorData data) {
  if (data.turbidity > 800 || data.flow < 50) {
    return "shutdown";
  } else if (data.anomaly) {
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

void printStatus(SensorData data, String decision) {
  Serial.printf("Flow: %.0f | Turbidity: %.0f | Decision: %s\n", 
                data.flow, data.turbidity, decision.c_str());
}
