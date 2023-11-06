#include <Servo.h>

const int TRIGGER_PIN_FRONT = 36;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 37;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = 38;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 39;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = 40;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 41;     // Right sonar sensor echo pin

const int motor1 = 4;
const int motor2 = 9;
const int pwm = 6;
const int ENCA = 20; // Encoder pulse input A
const int ENCB = 21; // Encoder pulse input B

Servo steeringServo;

const int forwardSpeed = 150; // Adjust this value for the desired forward speed
const int turnSpeed = 130;    // Adjust this value for the desired turn speed

volatile long posi = 0; // Use long to accommodate larger position values

void setup() {
  Serial.begin(9600);
  steeringServo.attach(A8);

  // Motor
  pinMode(motor1, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(motor2, OUTPUT);

  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);

  // Encoder
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

  Serial.println("Car position calculation using encoder pulses...");
}

void loop() {
  int distanceFront = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
  int distanceLeft = getDistance(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
  int distanceRight = getDistance(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);

  // Print sensor readings
  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Right Distance: ");
  Serial.print(distanceRight);
  Serial.print(" cm, Current position: ");
  Serial.println(posi);

  // Stop the car if pulse count is greater than 34000
  if (posi > 93500 && posi < 950000 ) {
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    analogWrite(pwm, 0);
    Serial.println("Car stopped");
    while (true);  // This will halt the program and effectively stop the car
  }

  // Implement obstacle avoidance based on sensor readings
  if (distanceFront >= 0 && distanceFront <= 50) {
    // Obstacle avoidance logic
    if (distanceLeft < distanceRight) {
      steeringServo.write(50);
      moveForward(turnSpeed);
      delay(500);
    } else if (distanceRight < distanceLeft) {
      steeringServo.write(130);
      moveForward(turnSpeed);
      delay(500);
    }
  } else {
    moveForward(forwardSpeed);
    steeringServo.write(90);
  }

  if (distanceFront >= 40) {
    // Obstacle avoidance logic when distanceFront is greater than or equal to 40
    if (distanceLeft < distanceRight) {
      steeringServo.write(70);
      moveForward(turnSpeed);
      delay(30);
    }
    if (distanceRight < distanceLeft) {
      steeringServo.write(100);
      moveForward(turnSpeed);
      delay(30);
    }
  }
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(triggerPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0343 / 2;
  return distance;
}

void moveForward(int speed) {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  analogWrite(pwm, speed);
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}
