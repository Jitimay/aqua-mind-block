# Real Tuya Integration Setup

## ✅ Your Tuya Project Details
- **Project**: AquaMindBlock
- **Access ID**: mraudgsm5fs77tj8wmyf
- **Project Code**: p1765985685343j83nve
- **Data Center**: Western Europe
- **Endpoint**: https://openapi-weeu.tuyaeu.com

## Step 1: Update WiFi Credentials
```cpp
// In aquamind_tuya_real.ino, update these lines:
const char* ssid = "YOUR_ACTUAL_WIFI_NAME";
const char* password = "YOUR_ACTUAL_WIFI_PASSWORD";
```

## Step 2: Create Device in Tuya Console
1. Go to https://iot.tuya.com
2. Login with your account
3. Go to "Device Management" → "Add Device"
4. Create device with ID: "aquamind_001"
5. Note the Device ID and Secret

## Step 3: Deploy Cloud Function
1. Go to "Cloud Development" → "Cloud Functions"
2. Create new function: "aquamind-ai-agent"
3. Upload `tuya_cloud_function.js`
4. Set trigger: HTTP webhook

## Step 4: Test Integration
```bash
# Upload aquamind_tuya_real.ino to ESP32
# Monitor serial output for:
# "✅ Tuya token obtained"
# "☁️ Tuya Cloud decision received"
```

## Step 5: Monitor in Tuya Console
- Device data should appear in real-time
- Check "Device Logs" for communication
- View "Cloud Function Logs" for AI decisions

## API Endpoints Used
- Token: `/v1.0/token?grant_type=1`
- Device Data: `/v1.0/iot-03/devices/data`
- Commands: `/v1.0/devices/{device_id}/commands`

## Expected Flow
```
ESP32 → WiFi → Tuya EU Cloud → AI Function → Decision → ESP32 → Actuators
```

## Troubleshooting
- Check WiFi connection first
- Verify token acquisition in serial monitor
- Ensure device is registered in Tuya console
- Check cloud function logs for errors
