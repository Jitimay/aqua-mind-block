# AquaMind Blocks - Prototype Wiring

## Minimal Hardware Setup

### ESP32 Connections
```
Sensors:
- Flow Sensor (YF-S201) → GPIO 36 (A0)
- Turbidity Sensor → GPIO 39 (A1)

Actuators:
- Pump Relay → GPIO 2
- Valve 1 Servo → GPIO 5
- Valve 2 Servo → GPIO 18
- Status LED → GPIO 13

Power:
- 5V → VIN
- GND → GND
```

### Quick Test Setup
1. Connect sensors to breadboard
2. Wire servos to GPIO pins
3. Connect relay module for pump
4. Power with USB (development) or 5V supply

### Sensor Simulation (if no real sensors)
```cpp
// In code, replace analogRead() with:
float simulateFlow() { return random(400, 600); }
float simulateTurbidity() { return random(200, 800); }
```

## Assembly Steps
1. Mount ESP32 on breadboard
2. Connect sensors with jumper wires
3. Attach servos to valve positions
4. Connect relay to pump/LED for demo
5. Test each component individually
