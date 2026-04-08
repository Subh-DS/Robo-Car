# ESP32 Autonomous Obstacle Avoidance Robot Car (Voice + Manual Control)

## Overview
This project presents a multi-mode ESP32-based robotic car capable of autonomous navigation, manual control, and voice-based control using Google Speech-to-Text.

The system integrates ultrasonic and IR sensors for obstacle detection, Bluetooth communication for command transmission, and a servo-based scanning mechanism for intelligent navigation.

---

## Key Features
- Autonomous obstacle avoidance using ultrasonic + IR sensors
- Manual control via Bluetooth commands
- Voice control using Google Speech-to-Text
- Servo-based directional scanning
- Real-time motor control using TB6612FNG driver
- Multi-mode switching (Auto / Manual / Voice)

---

## System Architecture

Mobile App → Speech-to-Text → Bluetooth → ESP32 → Motor Driver → Motors

Sensors (Ultrasonic + IR) → ESP32 → Decision Logic → Movement

---

## Hardware Components
- ESP32 DevKit V1
- HC-SR04 Ultrasonic Sensor
- IR Sensors (Left + Right)
- TB6612FNG Motor Driver
- DC Gear Motors
- Servo Motor
- Li-ion Battery + BMS
- DC-DC Buck Converter

---

## Hardware Setup

### Full Robot Setup
<img width="433" height="576" alt="Setup" src="https://github.com/user-attachments/assets/98edc5b5-fd1f-46c1-addb-10ca6af73631" />


### Obstacle Testing
![Testing-4](https://github.com/user-attachments/assets/40753746-81ca-400e-a256-362028f2af7c)
![Testing-2](https://github.com/user-attachments/assets/eaaaa3c2-d24b-4cbf-b46d-dca6fa2616ef)
![Testing-3](https://github.com/user-attachments/assets/d8ebe23e-fafd-4b2e-a858-b4c1d14c40db)
![Testing-1](https://github.com/user-attachments/assets/2c5a072a-c390-4b87-be15-b52448396372)



### Mobile App Interface
![Voice mode](https://github.com/user-attachments/assets/656473f0-bc00-4dbc-84bd-a3bc2ed8ea12)


---

## Working Explanation

### Autonomous Mode
- Ultrasonic sensor scans forward distance
- Servo rotates sensor for left-right scanning
- Robot selects direction with maximum clearance

### Manual Mode
- Commands received via Bluetooth (F, B, L, R, S)
- ESP32 parses commands and drives motors

### Voice Mode
- User speaks via mobile app
- Speech converted to text (Google STT)
- Commands sent to ESP32 via Bluetooth

---

## Command Mapping

| Command | Action |
|--------|--------|
| F | Forward |
| B | Backward |
| L | Left |
| R | Right |
| S | Stop |

---

## Code Snippet (Command Handling)

```cpp
if(cmd == "forward") moveForward();
else if(cmd == "back") moveBackward();
else if(cmd == "left") turnLeft();
else if(cmd == "right") turnRight();
else if(cmd == "stop") stopMotors();


