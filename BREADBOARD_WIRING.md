# Breadboard Testing Setup

## Components Needed
- 1x ESP32 development board
- 2x 10kΩ potentiometers  
- 5x LEDs (any color)
- 5x 220Ω resistors
- 1x Breadboard
- Jumper wires

## Wiring Diagram

```
ESP32 Pin    →    Component
---------         ---------
A0          →    Potentiometer 1 (Flow)
A1          →    Potentiometer 2 (Turbidity)
GPIO 2      →    LED 1 (Pump) → 220Ω → GND
GPIO 5      →    LED 2 (Valve 1) → 220Ω → GND  
GPIO 18     →    LED 3 (Valve 2) → 220Ω → GND
GPIO 19     →    LED 4 (Valve 3) → 220Ω → GND
GPIO 21     →    LED 5 (Valve 4) → 220Ω → GND
3.3V        →    Potentiometer VCC
GND         →    Potentiometer GND & LED common
```

## Testing Procedure

### Step 1: Upload Code
1. Open `aquamind_hardware_test.ino` in Arduino IDE
2. Update WiFi credentials (optional)
3. Select ESP32 board and port
4. Upload code

### Step 2: Test Scenarios

#### Normal Operation
- Set both potentiometers to middle position
- **Expected**: All 5 LEDs should be ON
- **Serial**: "🟢 NORMAL: All systems operational"

#### Contamination Detection  
- Turn turbidity potentiometer to high (75%+)
- **Expected**: Pump LED ON, Valve 1 LED OFF, others ON
- **Serial**: "🟡 PURIFY: Contaminated line isolated"

#### Emergency Shutdown
- Turn both potentiometers to extreme positions
- **Expected**: All LEDs OFF
- **Serial**: "🔴 EMERGENCY: All systems OFF"

#### Low Flow Alert
- Turn flow potentiometer to low (25%-)
- **Expected**: Purification mode activated
- **Serial**: Shows low flow detection

### Step 3: Monitor Serial Output
```
Flow: 500 | Turbidity: 300 | Decision: normal
🟢 NORMAL: All systems operational

Flow: 450 | Turbidity: 750 | Decision: purify  
🟡 PURIFY: Contaminated line isolated

Flow: 100 | Turbidity: 900 | Decision: shutdown
🔴 EMERGENCY: All systems OFF
```

## Troubleshooting

### No LED Response
- Check wiring connections
- Verify resistor values (220Ω)
- Test LED polarity (long leg = positive)

### Erratic Readings
- Check potentiometer connections
- Ensure stable power supply
- Add small delay in code if needed

### WiFi Issues
- Update credentials in code
- WiFi connection is optional for testing
- System works offline

## Real Hardware Upgrade

To test with actual water sensors:
1. Replace potentiometers with real sensors
2. Replace LEDs with relays + actuators
3. Add proper power supply (12V for pumps)
4. Use waterproof enclosures
