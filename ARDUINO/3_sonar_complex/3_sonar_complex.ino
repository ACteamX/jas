#include <Servo.h>

// Sonar sensor pins
const int TRIG_PIN_FRONT = 9;
const int ECHO_PIN_FRONT = 10;
const int TRIG_PIN_LEFT = 11;
const int ECHO_PIN_LEFT = 12;
const int TRIG_PIN_RIGHT = 13;
const int ECHO_PIN_RIGHT = A0;

// Servo and ESC pins
const int STEERING_PIN = 5;
const int ESC_PIN = 6;

// Sonar measurement variables
float frontDistance, leftDistance, rightDistance;

// Car movement variables
const int turnSpeed = 1500; // ESC signal value for turning (mid-speed)
const int straightSpeed = 2000; // ESC signal value for straight movement (high-speed)
const int stopSpeed = 1000; // ESC signal value to stop the motor

// Create Servo and ESC objects
Servo steeringServo;
Servo esc;

void setup() {
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);
  pinMode(STEERING_PIN, OUTPUT);
  pinMode(ESC_PIN, OUTPUT);

  // Attach Servo and ESC
  steeringServo.attach(STEERING_PIN);
  esc.attach(ESC_PIN);

  // Set initial speed to minimum (stopped)
  setMotorSpeed(stopSpeed);

  // Delay for ESC initialization
  delay(2000);
}

void loop() {
  // Read distances from sonar sensors
  frontDistance = getSonarDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT);
  leftDistance = getSonarDistance(TRIG_PIN_LEFT, ECHO_PIN_LEFT);
  rightDistance = getSonarDistance(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT);
  
  // Print distances for debugging
  Serial.print("Front: ");
  Serial.print(frontDistance);
  Serial.print(" | Left: ");
  Serial.print(leftDistance);
  Serial.print(" | Right: ");
  Serial.println(rightDistance);
  
  // Avoid obstacles and navigate through the arena
  if (frontDistance < 50 || leftDistance < 50 || rightDistance < 50) {
    // Obstacle detected, stop the car and avoid it
    stopMotor();
    
    // Avoid obstacle by turning away
    if (leftDistance > rightDistance) {
      steerLeft();
    } else {
      steerRight();
    }

    delay(1000); // Adjust the delay for the desired turn angle and maneuverability

    // Continue moving forward after avoiding the obstacle
    steerStraight();
    driveForwardHighSpeed();
    delay(1000); // Adjust the delay for the desired forward movement time
  } else {
    // No obstacles nearby, continue moving forward at high speed
    steerStraight();
    driveForwardHighSpeed();
  }
}

float getSonarDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2.0) * 0.0343;
  return distance;
}

void steerLeft() {
  steeringServo.write(45); // Adjust the servo angle for left turn
}

void steerRight() {
  steeringServo.write(135); // Adjust the servo angle for right turn
}

void steerStraight() {
  steeringServo.write(90); // Adjust the servo angle for straight steering
}

void driveForwardHighSpeed() {
  setMotorSpeed(straightSpeed); // Adjust the ESC signal for high-speed forward
}

void stopMotor() {
  setMotorSpeed(stopSpeed); // Set the ESC signal to stop the motor
}

void setMotorSpeed(int speed) {
  esc.writeMicroseconds(speed);
}
