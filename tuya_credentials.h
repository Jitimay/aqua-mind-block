// AquaMind Blocks - Tuya Credentials
// Real credentials from Tuya IoT Platform

#ifndef TUYA_CREDENTIALS_H
#define TUYA_CREDENTIALS_H

// Tuya Project Information
#define TUYA_ACCESS_ID "mraudgsm5fs77tj8wmyf"
#define TUYA_ACCESS_SECRET "4733aa38304f4ac5b235ae3984c137f9"
#define TUYA_PROJECT_CODE "p1765985685343j83nve"
#define TUYA_ENDPOINT "https://openapi-weeu.tuyaeu.com"
#define TUYA_DATA_CENTER "Western Europe"

// Device Configuration
#define DEVICE_NAME "AquaMind Blocks"
#define DEVICE_CATEGORY "wf" // Water Management
#define DEVICE_VERSION "1.0.0"

// WiFi Configuration - UPDATE THESE
#define WIFI_SSID "YOUR_WIFI_NETWORK"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Hardware Pin Definitions
#define FLOW_SENSOR_PIN A0
#define TURBIDITY_SENSOR_PIN A1
#define PUMP_RELAY_PIN 2
#define VALVE_1_PIN 5
#define VALVE_2_PIN 18
#define VALVE_3_PIN 19
#define VALVE_4_PIN 21

// AI Thresholds
#define TURBIDITY_ALERT_THRESHOLD 600
#define TURBIDITY_EMERGENCY_THRESHOLD 800
#define FLOW_MINIMUM_THRESHOLD 50
#define FLOW_ALERT_THRESHOLD 100

#endif
