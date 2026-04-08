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

<img width="433" height="576" alt="WhatsApp_Image_2026-03-31_at_11 10 57_PM__1_-removebg-preview" src="https://github.com/user-attachments/assets/eafe0ebe-ff59-4265-8610-1fa267dd83de" />

<img width="576" height="433" alt="car_pic-removebg-preview" src="https://github.com/user-attachments/assets/c6c4eeb6-9139-47a3-998c-410861637a4f" />

<img width="433" height="576" alt="WhatsApp_Image_2026-03-31_at_11 10 58_PM-removebg-preview" src="https://github.com/user-attachments/assets/90d7904d-6e8a-481d-919d-f7f793b076dd" />



