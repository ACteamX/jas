#include <Servo.h>

const int TRIGGER_PIN_FRONT = 8;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 9;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = 10;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 11;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = 12;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 13;     // Right sonar sensor echo pin

const int TRIGGER_PIN_LEFT_CORNER = 51;  // Left corner sonar sensor trigger pin
const int ECHO_PIN_LEFT_CORNER = 50;     // Left corner sonar sensor echo pin

const int TRIGGER_PIN_RIGHT_CORNER = 53;  // Right corner sonar sensor trigger pin
const int ECHO_PIN_RIGHT_CORNER = 52;     // Right corner sonar sensor echo pin

const int MAX_DISTANCE = 200; // Maximum distance to detect obstacles (in cm)

const int SERVO_PIN = A0;   // Servo motor control pin

const int MOTOR_PIN1 = 4; // Motor control pin 1
const int MOTOR_PIN2 = 5; // Motor control pin 2
const int enA = 6;

Servo steeringServo;

const int forwardSpeed = 100; // Adjust this value for the desired forward speed
const int turnSpeed = 80;     // Adjust this value for the desired turn speed

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
  // Corner Sensors
  pinMode(TRIGGER_PIN_LEFT_CORNER, OUTPUT);
  pinMode(ECHO_PIN_LEFT_CORNER, INPUT);
  pinMode(TRIGGER_PIN_RIGHT_CORNER, OUTPUT);
  pinMode(ECHO_PIN_RIGHT_CORNER, INPUT);
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

int getDistanceLeftCorner() {
  return getDistance(TRIGGER_PIN_LEFT_CORNER, ECHO_PIN_LEFT_CORNER);
}

int getDistanceRightCorner() {
  return getDistance(TRIGGER_PIN_RIGHT_CORNER, ECHO_PIN_RIGHT_CORNER);
}
// ... (previous code)




void loop() {
  int distanceFront = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
  int distanceLeft = getDistance(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
  int distanceRight = getDistance(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
  int distanceLeftCorner = getDistanceLeftCorner();
  int distanceRightCorner = getDistanceRightCorner();

  int total_left= (distanceLeft+distanceLeftCorner)/2;
  int total_right= (distanceRight+distanceRightCorner)/2;

  // Print sensor readings to Serial Monitor
  Serial.print("Front Distance: ");Serial.print(distanceFront);Serial.print(" cm, Left Distance: ");Serial.print(distanceLeft);
  Serial.print(" cm, Right Distance: ");Serial.print(distanceRight);Serial.print(" cm, Left Corner Distance: ");Serial.print(distanceLeftCorner);
  Serial.print(" cm, Right Corner Distance: ");Serial.print(distanceRightCorner);Serial.print(" cm ||");Serial.print(total_left);
  Serial.print(" cm  ||");Serial.print(total_right); Serial.println(" cm");

  delay(3000);

  if (distanceFront > 0 && distanceFront <= 50) {
    // Obstacle detected in front
    if (total_left < total_right ){
      // Obstacle detected on the left as well
      // Turn right
      Serial.println("Turning Right");
      steeringServo.write(0);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
      delay(2500);
    }
    else if (distanceRight < distanceLeft) {
      // Obstacle detected on the right as well
      // Turn left
      Serial.println("Turning Left");
      steeringServo.write(360);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
      delay(2500);
    }
    else if (distanceLeftCorner < distanceRightCorner) {
      // Obstacle detected on the left corner
      // Turn right
      Serial.println("Turning Right (Corner)");
      steeringServo.write(0);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
      delay(2500);
    }
    else if (distanceRightCorner < distanceLeftCorner) {
      // Obstacle detected on the right corner
      // Turn left
      Serial.println("Turning Left (Corner)");
      steeringServo.write(360);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
      delay(2500);
    }
  }
  else {
    // No obstacle in front, move forward and steer straight

    // Check if there's an obstacle on the left corner
    if (distanceLeftCorner < 30) {
      // Turn right
      Serial.println("Turning Right (Corner)");
      steeringServo.write(0);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
    }
    // Check if there's an obstacle on the right corner
    else if (distanceRightCorner < 30) {
      // Turn left
      Serial.println("Turning Left (Corner)");
      steeringServo.write(360);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, turnSpeed);
    }
    else {
      // No obstacle on the left or right corners, move forward and steer straight
      Serial.println("Moving Forward");
      steeringServo.write(100);
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
      analogWrite(enA, forwardSpeed);
    }
  }
}
