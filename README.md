# 🚗 Multi-Mode Robotic Car using ESP32

A smart robotic car built using ESP32 that operates in **three modes**:
- Manual Control (Bluetooth)
- Voice Control (Safe Mode)
- Autonomous Navigation (Obstacle Avoidance)

This project demonstrates real-world robotics concepts like sensor integration, decision-making, and wireless control.

---

## 📌 Features

- 🔵 **Manual Mode (Bluetooth Control)**
  - Control the car using commands: Forward, Backward, Left, Right, Stop
  - Real-time user control

- 🎤 **Voice Mode (Safe Control)**
  - Voice commands processed via mobile app
  - Built-in obstacle safety using IR + Ultrasonic sensors

- 🤖 **Autonomous Mode**
  - Smart obstacle avoidance
  - Uses ultrasonic + IR sensors
  - Servo-based 180° scanning for path selection

---

## 🧠 Working Principle

The ESP32 acts as the brain of the system:
- Receives commands via Bluetooth
- Processes sensor data (Ultrasonic + IR)
- Makes real-time decisions
- Controls motors using motor driver

---

## ⚙️ Hardware Components

- ESP32 Microcontroller  
- HC-SR04 Ultrasonic Sensor  
- IR Sensors (Left & Right)  
- SG90 Servo Motor  
- TB6612FNG Motor Driver  
- DC Motors + Chassis  
- 18650 Li-ion Batteries  
- Buck Converter  
- Capacitors & Resistors  

---

## 🔄 Modes of Operation

### 1. Manual Mode
- Controlled via Bluetooth commands:
  - F → Forward  
  - B → Backward  
  - L → Left  
  - R → Right  
  - S → Stop  

---

### 2. Voice Mode (Safe Mode)
- Commands:
  - "Go forward", "Go left", etc.
- Safety logic:
  - Stops if obstacle is too close
  - Avoids obstacles using IR sensors

---

### 3. Autonomous Mode
- Moves forward if path is clear  
- If obstacle detected:
  - Stops  
  - Scans left & right using servo  
  - Chooses best direction  

---

## 🔁 Algorithm (Simplified)

1. Initialize all components  
2. Select mode (Manual / Voice / Auto)  
3. Loop continuously:
   - Manual → Execute user commands  
   - Voice → Execute commands with safety checks  
   - Auto → Detect obstacles and navigate  

---

## 💻 How to Run

1. Install Arduino IDE / VS Code  
2. Install ESP32 board support  
3. Upload the code to ESP32  
4. Connect via Bluetooth  
5. Send commands from mobile app  

---

## 📷 Project Images

_Add your images here_
