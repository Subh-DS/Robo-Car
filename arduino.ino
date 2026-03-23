#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// -------- MOTOR DRIVER --------
#define AIN1 26
#define AIN2 27
#define PWMA 25
#define BIN1 14
#define BIN2 12
#define PWMB 13

// -------- ULTRASONIC --------
#define TRIG 4
#define ECHO 5

// -------- IR --------
#define IR_LEFT  32
#define IR_RIGHT 19

// -------- SERVO --------
#define SERVO_PIN 18

// -------- SETTINGS --------
int speedForward = 150;
int speedTurn = 90;

int warningDistance = 40;
int criticalDistance = 20;

// -------- MODES --------
enum Mode { IDLE, MANUAL, VOICE, AUTO };
Mode currentMode = IDLE;

enum MoveState { STOPPED, FORWARD, BACKWARD, LEFT, RIGHT };
MoveState moveState = STOPPED;

// =====================================================
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_ROBOT");

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(IR_LEFT, INPUT_PULLUP);
  pinMode(IR_RIGHT, INPUT_PULLUP);

  ledcAttach(PWMA, 1000, 8);
  ledcAttach(PWMB, 1000, 8);

  ledcAttach(SERVO_PIN, 50, 16);
  setServoAngle(90);

  Serial.println("Modes: manual / voice / auto");
}

// =====================================================
void loop() {

  if (SerialBT.available()) {

    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();

    Serial.println("CMD: " + cmd);

    // -------- MODE --------
    if (cmd == "manual mode") {
      currentMode = MANUAL;
      moveState = STOPPED;
      stopMotors();
      return;
    }

    if (cmd == "voice mode") {
      currentMode = VOICE;
      moveState = STOPPED;
      stopMotors();
      return;
    }

    if (cmd == "auto mode" || cmd == "autonomous") {
      currentMode = AUTO;
      moveState = STOPPED;
      stopMotors();
      return;
    }

    // -------- MANUAL --------
    if (currentMode == MANUAL) {
      if (cmd == "f") moveState = FORWARD;
      else if (cmd == "b") moveState = BACKWARD;
      else if (cmd == "l") moveState = LEFT;
      else if (cmd == "r") moveState = RIGHT;
      else if (cmd == "s") moveState = STOPPED;
    }

    // -------- VOICE --------
    if (currentMode == VOICE) {
      if (cmd == "go forward") moveState = FORWARD;
      else if (cmd == "go backward") moveState = BACKWARD;
      else if (cmd == "go left") moveState = LEFT;
      else if (cmd == "go right") moveState = RIGHT;
      else if (cmd == "stop") moveState = STOPPED;
    }
  }

  // =====================================================
  // 🎮 MANUAL
  if (currentMode == MANUAL) {
    executeMovement();
  }

  // =====================================================
  // 🎤 VOICE (SAFE)
  if (currentMode == VOICE) {

    int dist = readDistance();
    bool leftBlocked = digitalRead(IR_LEFT) == LOW;
    bool rightBlocked = digitalRead(IR_RIGHT) == LOW;

    if (dist < criticalDistance) {
      stopMotors();
      return;
    }

    if (leftBlocked) {
      moveRightSmooth();
      return;
    }

    if (rightBlocked) {
      moveLeftSmooth();
      return;
    }

    executeMovement();
  }

  // =====================================================
  // 🤖 AUTO (FULL SMART)
  if (currentMode == AUTO) {
    autonomousDrive();
  }
}

// =====================================================
// 🔁 MOVEMENT
void executeMovement() {
  switch (moveState) {
    case FORWARD: moveForward(); break;
    case BACKWARD: moveBackward(); break;
    case LEFT: turnLeft(); break;
    case RIGHT: turnRight(); break;
    case STOPPED: stopMotors(); break;
  }
}

// =====================================================
// MOTOR CONTROL
void moveForward() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
  ledcWrite(PWMA, speedForward);
  ledcWrite(PWMB, speedForward);
}

void moveBackward() {
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
  ledcWrite(PWMA, speedForward);
  ledcWrite(PWMB, speedForward);
}

void turnLeft() {
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
  ledcWrite(PWMA, speedTurn);
  ledcWrite(PWMB, speedTurn);
}

void turnRight() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
  ledcWrite(PWMA, speedTurn);
  ledcWrite(PWMB, speedTurn);
}

void moveLeftSmooth() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
  ledcWrite(PWMA, speedTurn);
  ledcWrite(PWMB, speedForward);
}

void moveRightSmooth() {
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
  ledcWrite(PWMA, speedForward);
  ledcWrite(PWMB, speedTurn);
}

void stopMotors() {
  ledcWrite(PWMA, 0);
  ledcWrite(PWMB, 0);
}

// =====================================================
// ULTRASONIC
int readDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  int distance = duration * 0.034 / 2;

  if (distance == 0 || distance > 400)
    distance = 400;

  return distance;
}

// =====================================================
// SERVO
void setServoAngle(int angle) {
  uint32_t duty = map(angle, 0, 180, 1638, 8192);
  ledcWrite(SERVO_PIN, duty);
}

// =====================================================
// SCAN
int scanDirection(bool left) {

  int best = 0;

  if (left) {
    for (int a = 90; a <= 160; a += 5) {
      setServoAngle(a);
      delay(20);
      best = max(best, readDistance());
    }
  } else {
    for (int a = 90; a >= 20; a -= 5) {
      setServoAngle(a);
      delay(20);
      best = max(best, readDistance());
    }
  }

  setServoAngle(90);
  delay(200);
  return best;
}

// =====================================================
// 🤖 AUTO MODE (FULL AI)
void autonomousDrive() {

  bool leftBlocked = digitalRead(IR_LEFT) == LOW;
  bool rightBlocked = digitalRead(IR_RIGHT) == LOW;

  // IR priority
  if (leftBlocked && !rightBlocked) {
    moveRightSmooth();
    delay(300);
    return;
  }

  if (rightBlocked && !leftBlocked) {
    moveLeftSmooth();
    delay(300);
    return;
  }

  int frontDist = readDistance();

  if (frontDist > warningDistance) {
    moveForward();
  }
  else if (frontDist > criticalDistance) {
    moveForward();
  }
  else {
    stopMotors();
    delay(200);

    int leftDist = scanDirection(true);
    int rightDist = scanDirection(false);

    if (leftDist > rightDist) {
      moveLeftSmooth();
      delay(600);
    } else {
      moveRightSmooth();
      delay(600);
    }

    stopMotors();
  }
}