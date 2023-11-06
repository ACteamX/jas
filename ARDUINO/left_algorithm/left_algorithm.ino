#include <Servo.h>

const int TRIGGER_PIN = 8;  // Sonar sensor trigger pin
const int ECHO_PIN = 9;     // Sonar sensor echo pin
const int MAX_DISTANCE = 200; // Maximum distance to detect obstacles (in cm)

const int SERVO_PIN = A0;   // Servo motor control pin

const int MOTOR_PIN1 = 2; // Motor control pin 1
const int MOTOR_PIN2 = 3; // Motor control pin 2
const int enA = 6;

Servo steeringServo;

const int forwardSpeed = 150; // Adjust this value for the desired forward speed
const int turnSpeed = 150;     // Adjust this value for the desired turn speed

void setup() {
  Serial.begin(9600);
  steeringServo.attach(SERVO_PIN);
  // Motor
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(enA, OUTPUT);
  // Sonar Sensor
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = (duration*0.0343 )/2 ;
  Serial.println(distance);

  if (distance > 0 && distance <= 30) {
    // Obstacle detected, avoid it
    // Backward
   /* steeringServo.write(60); // Adjust this angle for the desired backward direction
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, HIGH);
    analogWrite(enA, 250);
    delay(700);
*/
/*    // Stop the motor after backing up
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, HIGH);
    analogWrite(enA, 0);
    delay(300);
*/
// Randomly turn left or right
      steeringServo.write(0); // Adjust this angle for the desired left turn direction
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, 150);
      delay(1000);
   } else {
    // No obstacle, move forward and steer straight
    steeringServo.write(60); // Adjust this angle for the desired straight position
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
    analogWrite(enA, 200);
  }
}
