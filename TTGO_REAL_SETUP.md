# TTGO ESP32 Real Hardware Test

## Your Hardware
- ✅ TTGO ESP32 (LilyGO T-Call or similar)
- ✅ Real Tuya Cloud credentials
- ✅ WiFi network access

## Quick Setup (10 minutes)

### Step 1: Update Code
```cpp
// In ttgo_real_test.ino, update these:
const char* ssid = "YOUR_ACTUAL_WIFI_NAME";
const char* password = "YOUR_ACTUAL_WIFI_PASSWORD";
```

### Step 2: Hardware Connections
```
TTGO ESP32 Pin    →    Component
--------------         ---------
GPIO 36 (ADC)     →    Potentiometer 1 (Flow sensor)
GPIO 39 (ADC)     →    Potentiometer 2 (Turbidity sensor)
GPIO 2 (LED)      →    Built-in LED (Pump indicator)
GPIO 4            →    External LED (Valve 1)
GPIO 16           →    External LED (Valve 2)
GPIO 17           →    External LED (Valve 3)
GPIO 5            →    External LED (Valve 4)
```

### Step 3: Upload & Test
1. Open Arduino IDE
2. Select "ESP32 Dev Module" board
3. Upload `ttgo_real_test.ino`
4. Open Serial Monitor (115200 baud)

## Expected Serial Output
```
Connecting to WiFi....
✅ WiFi connected
IP: 192.168.1.100
Token request: 200
✅ Tuya token obtained
🌊 AquaMind TTGO Real Test Ready

Flow: 500 | Turbidity: 300 | Decision: normal
🟢 NORMAL: All systems operational
☁️ Tuya send: 200
Tuya response: {"success":true}

Flow: 450 | Turbidity: 750 | Decision: purify
🟡 PURIFY: Contaminated line isolated
☁️ Tuya send: 200
```

## Real Testing Scenarios

### Test 1: Normal Operation
- **Action**: Touch GPIO 36 and 39 lightly (or use pots at mid-position)
- **Expected**: All LEDs ON, "normal" decision
- **Tuya**: Data sent to cloud every 30 seconds

### Test 2: Contamination Simulation
- **Action**: Touch GPIO 39 firmly (high turbidity)
- **Expected**: Valve 1 LED OFF, others ON, "purify" decision
- **Tuya**: Cloud receives contamination alert

### Test 3: Emergency Shutdown
- **Action**: Touch both pins firmly (extreme values)
- **Expected**: All LEDs OFF, "shutdown" decision
- **Tuya**: Emergency status sent to cloud

## Tuya Cloud Monitoring

### Check Your Data
1. Go to https://iot.tuya.com
2. Login to your account
3. Go to "Device Management"
4. Look for device "aquamind_ttgo_001"
5. View real-time data and commands

### Expected Data Points
```json
{
  "device_id": "aquamind_ttgo_001",
  "commands": [
    {"code": "flow", "value": 500},
    {"code": "turbidity", "value": 300},
    {"code": "decision", "value": "normal"}
  ]
}
```

## Troubleshooting

### WiFi Connection Issues
- Check SSID and password
- Ensure 2.4GHz network (ESP32 doesn't support 5GHz)
- Try mobile hotspot if needed

### Tuya Token Issues
- Check internet connection
- Verify credentials are correct
- Token expires - code will retry automatically

### Sensor Reading Issues
- TTGO touch pins are sensitive
- Use potentiometers for stable readings
- Check pin connections

## Real Water Sensors (Optional)
To upgrade to actual water sensors:
```cpp
// Replace touch sensing with real sensors
float flow = readFlowSensor();        // YF-S201 flow sensor
float turbidity = readTurbiditySensor(); // TSD-10 turbidity sensor
```

## Demo Video Ready!
Once working, you have:
- ✅ Real ESP32 hardware
- ✅ Actual Tuya Cloud integration
- ✅ Live data transmission
- ✅ AI decision making
- ✅ Hardware control responses

Perfect for hackathon demo video!
