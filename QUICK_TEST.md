# Quick Hardware Test - 15 Minutes

## What You Need
- ESP32 board
- 2 potentiometers  
- 5 LEDs + resistors
- Breadboard

## 5-Minute Wiring
```
Pot 1 → A0 (flow sensor)
Pot 2 → A1 (turbidity sensor)
5 LEDs → GPIO 2,5,18,19,21 (pump + valves)
```

## Upload & Test
1. Upload `aquamind_hardware_test.ino`
2. Open Serial Monitor (115200 baud)
3. Adjust potentiometers and watch LEDs

## Expected Results
- **Both pots middle**: All LEDs ON
- **Turbidity pot high**: 1 LED OFF (contaminated valve)
- **Both pots extreme**: All LEDs OFF (emergency)

## Demo Video Ready!
Once working, you can record:
- Show normal operation (all LEDs on)
- Simulate contamination (turn pot, LED goes off)
- Show emergency response (all LEDs off)
- Explain AI decision making in real-time

This gives you a **working hardware demo** for the hackathon submission!
