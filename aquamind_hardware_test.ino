#include <WiFi.h>

// WiFi credentials - UPDATE THESE
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Hardware pins
#define FLOW_PIN A0
#define TURBIDITY_PIN A1
#define PUMP_LED 2
#define VALVE_LEDS {5, 18, 19, 21}

int valve_pins[] = VALVE_LEDS;

void setup() {
  Serial.begin(115200);
  
  // Initialize LED pins
  pinMode(PUMP_LED, OUTPUT);
  for(int i = 0; i < 4; i++) {
    pinMode(valve_pins[i], OUTPUT);
  }
  
  // Connect WiFi (optional)
  WiFi.begin(ssid, password);
  
  Serial.println("🌊 AquaMind Hardware Test Ready");
  Serial.println("Adjust potentiometers to test scenarios:");
  Serial.println("- Normal: Both pots at mid-position");
  Serial.println("- Contamination: Turbidity pot high");
  Serial.println("- Emergency: Both pots extreme");
}

void loop() {
  // Read sensor values (0-4095 on ESP32)
  int flow = analogRead(FLOW_PIN);
  int turbidity = analogRead(TURBIDITY_PIN);
  
  // Convert to 0-1000 range for easier testing
  float flowValue = map(flow, 0, 4095, 0, 1000);
  float turbidityValue = map(turbidity, 0, 4095, 0, 1000);
  
  // AI Decision Logic
  String decision = makeDecision(flowValue, turbidityValue);
  
  // Execute hardware control
  executeDecision(decision);
  
  // Print status
  Serial.printf("Flow: %3.0f | Turbidity: %3.0f | Decision: %s\n", 
                flowValue, turbidityValue, decision.c_str());
  
  delay(1000);
}

String makeDecision(float flow, float turbidity) {
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
  if(decision == "shutdown") {
    // Emergency: All off
    digitalWrite(PUMP_LED, LOW);
    for(int i = 0; i < 4; i++) {
      digitalWrite(valve_pins[i], LOW);
    }
    Serial.println("🔴 EMERGENCY: All systems OFF");
    
  } else if(decision == "purify") {
    // Purify: Pump on, close contaminated valve
    digitalWrite(PUMP_LED, HIGH);
    digitalWrite(valve_pins[0], LOW);  // Close contaminated
    for(int i = 1; i < 4; i++) {
      digitalWrite(valve_pins[i], HIGH); // Keep clean open
    }
    Serial.println("🟡 PURIFY: Contaminated line isolated");
    
  } else {
    // Normal: All on
    digitalWrite(PUMP_LED, HIGH);
    for(int i = 0; i < 4; i++) {
      digitalWrite(valve_pins[i], HIGH);
    }
    Serial.println("🟢 NORMAL: All systems operational");
  }
}
