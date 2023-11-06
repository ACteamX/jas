#include <Servo.h>

const int TRIGGER_PIN_FRONT = 8;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 9;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = 10;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 11;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = 12;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 13;     // Right sonar sensor echo pin

const int MAX_DISTANCE = 200; // Maximum distance to detect obstacles (in cm)

const int SERVO_PIN = A0;   // Servo motor control pin

const int MOTOR_PIN1 = 4; // Motor control pin 1
const int MOTOR_PIN2 = 5; // Motor control pin 2
const int enA = 6;

Servo steeringServo;

const int forwardSpeed = 250; // Adjust this value for the desired forward speed
const int turnSpeed = 130;     // Adjust this value for the desired turn speed

void setup() {
  Serial.begin(9600);
  steeringServo.attach(SERVO_PIN);
  // Motor
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(enA, OUTPUT);
  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(4);
  digitalWrite(triggerPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0343 / 2;
  return distance;
}

void loop() {
  int distanceFront = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
  int distanceLeft = getDistance(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
  int distanceRight = getDistance(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);

/*  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Right Distance: ");
  Serial.print(distanceRight);
  Serial.println(" cm");
*/
  if (distanceFront > 0 && distanceFront <= 50) {
    // Obstacle detected in front
    if (distanceLeft < distanceRight){
      //BACK FOR 1 SECOND
      steeringServo.write(90);
      digitalWrite(MOTOR_PIN1, LOW);
      digitalWrite(MOTOR_PIN2, HIGH);
      analogWrite(enA, 255);
      delay(1000);
      // Obstacle detected on the left as well
      // Turn right
      steeringServo.write(0);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
      delay(1500);}
     
    else if (distanceRight < distanceLeft) {
      // Obstacle detected on the right as well
      steeringServo.write(90);
      digitalWrite(MOTOR_PIN1, LOW);
      digitalWrite(MOTOR_PIN2, HIGH);
      analogWrite(enA, 255);
      delay(1000);
      // Turn left
      steeringServo.write(360);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
      delay(1500);
    } 
  }
  else {
    // No obstacle in front, move forward and steer straight
    steeringServo.write(100);
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
    analogWrite(enA, forwardSpeed);
  }
}
