# Hardware Testing Guide

## Required Hardware
- ESP32 development board
- 2x Potentiometers (simulate sensors)
- 4x LEDs (simulate valves)
- 1x LED (simulate pump)
- Breadboard and jumper wires

## Wiring for Testing

### Sensor Simulation
```
Potentiometer 1 (Flow) → ESP32 A0
Potentiometer 2 (Turbidity) → ESP32 A1
```

### Actuator Simulation  
```
LED 1 (Pump) → ESP32 GPIO 2 → 220Ω resistor → GND
LED 2 (Valve 1) → ESP32 GPIO 5 → 220Ω resistor → GND
LED 3 (Valve 2) → ESP32 GPIO 18 → 220Ω resistor → GND
LED 4 (Valve 3) → ESP32 GPIO 19 → 220Ω resistor → GND
LED 5 (Valve 4) → ESP32 GPIO 21 → 220Ω resistor → GND
```

## Test Steps

### 1. Upload Code
```bash
# Update WiFi credentials in aquamind_standalone.ino
# Upload to ESP32 via Arduino IDE
```

### 2. Test Scenarios
- **Normal**: Both potentiometers at mid-position
- **Contamination**: Turn turbidity pot to high
- **Low Flow**: Turn flow pot to low
- **Emergency**: Both pots to extreme positions

### 3. Expected Results
- **Normal**: All LEDs on
- **Purify**: Valve 1 LED off, others on
- **Shutdown**: All LEDs off
