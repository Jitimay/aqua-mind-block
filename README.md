# 🌊 AquaMind Blocks
**Build AI Water Infrastructure, As Easy As Stacking Blocks**

## Project Overview

AquaMind Blocks is a modular AI-powered water safety and management system that transforms traditional water infrastructure into intelligent, autonomous systems. Built for the Tuya AI Innovators Hackathon 2025.

## 🧩 Block Architecture

### 1. Sense Block (Arduino Nano RP2040)
- **Purpose**: Intelligent sensor data collection
- **Sensors**: Flow, pressure, turbidity, pH
- **AI**: Edge anomaly detection with TinyML
- **File**: `sense_block.ino`

### 2. Think Block (LilyGO TTGO T-Call ESP32)
- **Purpose**: AI decision making and cloud connectivity
- **Features**: Tuya AI integration, GSM backup, local AI
- **File**: `think_block.ino`

### 3. Act Block (Arduino Mega)
- **Purpose**: Physical system control
- **Actuators**: 8 servo valves, pump relay, NEMA 17 stepper
- **File**: `act_block.ino`

### 4. Vision Block (ESP32-CAM)
- **Purpose**: Visual water quality monitoring
- **Features**: Image capture, AI analysis, streaming
- **File**: `vision_block.ino`

### 5. Coordinator (STM32 Black Pill)
- **Purpose**: System orchestration and integration
- **Features**: Inter-block communication, decision coordination
- **File**: `coordinator.ino`

## 🚀 Quick Start

### Prerequisites
- Arduino IDE with ESP32 and STM32 board packages
- Tuya Developer Account
- AWS Account (for Kiro integration)
- Required hardware components (see WIRING_GUIDE.md)

### Setup Steps

1. **Clone and Configure**
   ```bash
   git clone <repository>
   cd AquamindBlock
   ```

2. **Update Configuration**
   - Edit `config.h` with your WiFi credentials
   - Add Tuya API keys
   - Set sensor calibration values

3. **Flash Firmware**
   - Upload `sense_block.ino` to Arduino Nano RP2040
   - Upload `think_block.ino` to ESP32 T-Call
   - Upload `act_block.ino` to Arduino Mega
   - Upload `vision_block.ino` to ESP32-CAM
   - Upload `coordinator.ino` to STM32 Black Pill

4. **Wire Hardware**
   - Follow connections in `WIRING_GUIDE.md`
   - Install water sensors in system
   - Connect actuators (pump, valves)

5. **Test System**
   ```
   Serial Monitor Commands:
   - "STATUS" - System status
   - "EMERGENCY_STOP" - Emergency shutdown
   - "RESET" - Reset to normal operation
   ```

## 📁 File Structure

```
AquamindBlock/
├── sense_block.ino          # Sensor data collection
├── think_block.ino          # AI decision making
├── act_block.ino           # Actuator control
├── vision_block.ino        # Visual monitoring
├── coordinator.ino         # System coordination
├── config.h               # System configuration
├── WIRING_GUIDE.md        # Hardware connections
└── README.md              # This file
```

## 🔧 Hardware Requirements

### Microcontrollers
- Arduino Nano RP2040
- LilyGO TTGO T-Call ESP32 SIM800L
- Arduino Mega 2560
- ESP32-CAM
- STM32 Black Pill

### Actuators & Sensors
- 8x Servo motors (valve control)
- 1x NEMA 17 stepper motor
- 1x Water pump
- 2x Relay modules
- Water sensors (flow, pressure, turbidity, pH)

### Power & Communication
- 12V DC power supply (5A minimum)
- Buck converter (12V to 5V)
- Jumper wires and breadboards
- Waterproof enclosures

## 🤖 AI Features

### Edge AI (TinyML)
- Real-time anomaly detection on Sense Block
- Offline operation capability
- Low power consumption

### Cloud AI (Tuya + AWS Kiro)
- Predictive analytics for system failures
- Water quality trend analysis
- Optimization algorithms for energy efficiency

### Decision Making
- Multi-factor risk assessment
- Autonomous emergency responses
- Explainable AI logging

## 🌍 Use Cases

- **Rural Water Systems**: Autonomous monitoring for remote communities
- **Smart Buildings**: Intelligent water management for offices/schools
- **Agriculture**: Precision irrigation control
- **Industrial**: Process water quality assurance
- **Emergency Response**: Rapid contamination detection

## 📊 System States

### Normal Operation
- Continuous monitoring
- Predictive maintenance alerts
- Energy optimization

### Purification Mode
- Contamination detected
- Automatic purification cycle
- Isolated contaminated lines

### Emergency Shutdown
- Critical failure detected
- All pumps stopped
- Valves closed
- SMS alerts sent

## 🔒 Safety Features

- **Fail-Safe Design**: System defaults to safe state on failure
- **Manual Override**: Physical emergency stop capability
- **Redundant Communication**: WiFi + GSM backup
- **Offline Operation**: Local decision making when disconnected
- **Audit Logging**: Complete action history

## 📱 Monitoring & Control

### Serial Interface
Real-time system monitoring via USB serial connection

### SMS Alerts
Emergency notifications via GSM module

### Tuya Cloud Dashboard
Remote monitoring and control through Tuya platform

### Voice Interface (Future)
Natural language interaction with system status

## 🛠️ Development

### Adding New Sensors
1. Update `config.h` with new pin definitions
2. Modify `sense_block.ino` to read new sensor
3. Update AI models to include new data

### Extending AI Capabilities
1. Train new models with AWS Kiro
2. Deploy to Tuya AI platform
3. Update `think_block.ino` decision logic

### Custom Actuators
1. Add hardware connections to `act_block.ino`
2. Implement control functions
3. Update coordinator communication protocol

## 🏆 Hackathon Alignment

**Primary Track**: Industry Solutions (AI + IoT)
**Secondary Track**: AI Agent Application

**Key Innovations**:
- Modular "block-based" architecture
- True AI vs rule-based automation
- Offline-first design for global deployment
- Integration with Tuya ecosystem

## 📞 Support

For technical support or questions:
- Check `WIRING_GUIDE.md` for hardware issues
- Review serial monitor output for debugging
- Test individual blocks separately for isolation

## 🔮 Future Roadmap

- **Phase 1**: Basic water monitoring and control
- **Phase 2**: Predictive maintenance algorithms
- **Phase 3**: Multi-site coordination and optimization
- **Phase 4**: Commercial deployment and scaling

---

**Built for Tuya AI Innovators Hackathon 2025**
*Making water infrastructure intelligent, one block at a time* 🧠💧
