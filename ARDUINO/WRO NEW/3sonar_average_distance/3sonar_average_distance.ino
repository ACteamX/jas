#include <Servo.h>

const int TRIGGER_PIN_FRONT = 36;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 37;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = 38;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 39;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = 41;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 42;     // Right sonar sensor echo pin

const int ren = 21; const int rpwm = 20; const int len = 19; const int lpwm = 18;

Servo steeringServo;

const int forwardSpeed = 130; // Adjust this value for the desired forward speed
const int turnSpeed = 130;     // Adjust this value for the desired turn speed  

void setup() {
  Serial.begin(9600);
  steeringServo.attach(A7);

  // Motor
  pinMode(ren, OUTPUT); pinMode(rpwm, OUTPUT); pinMode(len, OUTPUT); pinMode(lpwm, OUTPUT);
  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT); pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT); pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT); pinMode(ECHO_PIN_RIGHT, INPUT);
}

int getAverageDistance(int triggerPin, int echoPin, int numSamples) {
  long totalDistance = 0;
  for (int i = 0; i < numSamples; i++) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(1);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.0343 / 2;
    totalDistance += distance;
  }
  // Calculate the average distance
  int averageDistance = totalDistance / numSamples;
  return averageDistance;
}

void loop() {
  int numSamples = 5; // You can adjust this value based on the desired accuracy

  int sumFront = 0;
  int sumLeft = 0;
  int sumRight = 0;

  for (int i = 0; i < numSamples; i++) {
    int distanceFront = getAverageDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, 1);
    int distanceLeft = getAverageDistance(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, 1);
    int distanceRight = getAverageDistance(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, 1);

    sumFront += distanceFront;
    sumLeft += distanceLeft;
    sumRight += distanceRight;
/*
    Serial.print("Front Distance: ");
    Serial.print(distanceFront);
    Serial.print(" cm, Left Distance: ");
    Serial.print(distanceLeft);
    Serial.print(" cm, Right Distance: ");
    Serial.print(distanceRight);
    Serial.println(" cm");
    */
  }

  // Calculate average distances
  int averageFront = sumFront / numSamples;
  int averageLeft = sumLeft / numSamples;
  int averageRight = sumRight / numSamples;

  Serial.print("Average Front Distance: ");
  Serial.print(averageFront);
  Serial.print(" cm, Average Left Distance: ");
  Serial.print(averageLeft);
  Serial.print(" cm, Average Right Distance: ");
  Serial.print(averageRight);
  Serial.println(" cm");

  if (averageFront >= 50 && averageFront <= 70) {
    // Obstacle detected in front
    if (averageLeft < averageRight) {
      // Obstacle detected on the left as well
      // Turn right
      steeringServo.write(0);
      digitalWrite(ren, HIGH);
      digitalWrite(len, LOW);
      analogWrite(rpwm, turnSpeed);
      analogWrite(lpwm, 0);
      delay(600);
    } else if (averageRight < averageLeft) {
      // Obstacle detected on the right as well
      // Turn left
      steeringServo.write(180);
      digitalWrite(ren, HIGH);
      digitalWrite(len, LOW);
      analogWrite(rpwm, turnSpeed);
      analogWrite(lpwm, 0);
      delay(600);
    }
  } else {
    // No obstacle in front, move forward and steer straight
    steeringServo.write(90);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, forwardSpeed);
    analogWrite(lpwm, 0);
  }

  if (averageLeft < 15 ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(70);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 130);
    analogWrite(lpwm, 0);
    delay(50);
    //steeringServo.write(125);
  }
  if (averageRight < 15  ) {
    // Obstacle detected on the right as well
    // Turn right
    steeringServo.write(110);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 130);
    analogWrite(lpwm, 0);
    delay(50);
 
  }
  if ( averageFront >= 70) {

    if (averageLeft < averageRight ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(70);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 130);
    analogWrite(lpwm, 0);
    delay(50);
    //steeringServo.write(125);
  }
  if (averageRight < averageLeft  ) {
    // Obstacle detected on the right as well
    // Turn right
    steeringServo.write(110);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 130);
    analogWrite(lpwm, 0);
    delay(50);
 
  }
  }
}
