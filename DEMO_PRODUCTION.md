# Demo Video Production Guide

## Equipment Needed
- Smartphone/camera for recording
- Clear water container
- Food coloring (simulate contamination)
- Laptop showing Tuya app/serial monitor

## Shot List (2-3 minutes total)

### Scene 1: Introduction (20 seconds)
- **Shot**: Close-up of hardware setup
- **Script**: "AquaMind Blocks - AI water safety built on TuyaOpen"
- **Action**: Show ESP32, sensors, servos

### Scene 2: Normal Operation (30 seconds)
- **Shot**: Split screen - hardware + Tuya app
- **Script**: "Continuous monitoring with edge AI"
- **Action**: Show sensor readings, normal valve positions

### Scene 3: Contamination Event (45 seconds)
- **Shot**: Add food coloring to water
- **Script**: "Contamination detected - AI responds automatically"
- **Action**: 
  1. Add coloring to simulate turbidity
  2. Show sensor spike on serial monitor
  3. Show Tuya cloud decision
  4. Show valves closing automatically

### Scene 4: System Recovery (30 seconds)
- **Shot**: Clear water restoration
- **Script**: "System recovers automatically when safe"
- **Action**: Show valves reopening, normal operation

### Scene 5: Technical Highlights (15 seconds)
- **Shot**: Code on screen + TuyaOpen logo
- **Script**: "Built with TuyaOpen SDK - deploy anywhere"

## Recording Commands
```bash
# Start recording
# Run: arduino-cli upload aquamind_main.ino
# Open serial monitor
# Open Tuya Smart app
# Follow shot sequence above
```

## Post-Production
- Edit to 2-3 minutes
- Add hashtags: #TuyaOpen #TuyaAI #HackWithTuya
- Upload to YouTube
- Include in README.md
