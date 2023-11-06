#include <Servo.h>

const int TRIGGER_PIN_FRONT = 29;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 31;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = 37;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 39;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = 51;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 53;     // Right sonar sensor echo pin



const int ren = 21;const int rpwm = 20;const int len = 19;const int lpwm=18;

Servo steeringServo;

const int forwardSpeed = 180; // Adjust this value for the desired forward speed
const int turnSpeed = 150;     // Adjust this value for the desired turn speed  

void setup() {
  Serial.begin(9600);
  steeringServo.attach(47);
  
  // Motor
  pinMode(ren, OUTPUT);pinMode(rpwm, OUTPUT);pinMode(len, OUTPUT);pinMode(lpwm,OUTPUT);
  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT);pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);pinMode(ECHO_PIN_RIGHT, INPUT);

}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(1);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(triggerPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0343 / 2;
  return distance;
}

void loop() {
  int distanceFront = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
  int distanceLeft = getDistance(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
  int distanceRight = getDistance(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);

  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Right Distance: ");
  Serial.print(distanceRight);
  Serial.println(" cm");

  if (distanceFront >= 0  && distanceFront <= 60) {
  // Obstacle detected in front

 
  if ( distanceLeft < distanceRight ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(0);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, turnSpeed);
    analogWrite(lpwm, 0);
    delay(400);
  }
   else if ( distanceRight < distanceLeft ) {
    // Obstacle detected on the right as well
    // Turn left
    steeringServo.write(180);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, turnSpeed);
    analogWrite(lpwm, 0);
    delay(400);
  }
  }
   
 else {
  // No obstacle in front, move forward and steer straight
  steeringServo.write(90);
  digitalWrite(ren, HIGH);
  digitalWrite(len, LOW);
  analogWrite(rpwm, forwardSpeed);
  analogWrite(lpwm, 0);
}

/*
  if ( distanceLeft < 25 ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(70);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 140);
    analogWrite(lpwm, 0);
    delay(100);
 }
 
  if ( distanceRight < 25 ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(130);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 140);
    analogWrite(lpwm, 0);
    delay(100);
 }
*/

  if ( distanceFront >= 60){
  if ( distanceLeft < distanceRight ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(50);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 130);
    analogWrite(lpwm, 0);
    delay(40);
 }
 
  if ( distanceRight < distanceLeft ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(110);
    digitalWrite(ren, HIGH);
    digitalWrite(len, LOW);
    analogWrite(rpwm, 130);
    analogWrite(lpwm, 0);
    delay(40);
 }}
}

  
 
