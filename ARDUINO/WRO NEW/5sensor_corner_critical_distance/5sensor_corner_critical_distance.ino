#include <Servo.h>

const int TRIGGER_PIN_FRONT = 8;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 9;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = 10;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 11;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = 12;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 13;     // Right sonar sensor echo pin

const int ECHO_PIN_RIGHT_CORNER = 50;
const int TRIGGER_PIN_RIGHT_CORNER = 51;

const int ECHO_PIN_LEFT_CORNER = 52;
const int TRIGGER_PIN_LEFT_CORNER = 53;

const int SERVO_PIN = A7;   // Servo motor control pin

const int ren = 21;const int rpwm = 20;const int len = 19;const int lpwm=18;

Servo steeringServo;

const int forwardSpeed = 150; // Adjust this value for the desired forward speed
const int turnSpeed = 160;     // Adjust this value for the desired turn speed

void setup() {
  Serial.begin(9600);
  steeringServo.attach(SERVO_PIN);
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
  int distanceRightCorner = getDistance( TRIGGER_PIN_RIGHT_CORNER, ECHO_PIN_RIGHT_CORNER);
  int distanceLeftCorner = getDistance(TRIGGER_PIN_LEFT_CORNER, ECHO_PIN_LEFT_CORNER);
  int totalRight= (distanceRight + distanceRightCorner ) / 2;
  int totalLeft = (distanceLeft + distanceLeftCorner) / 2;

  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Right Distance: ");
  Serial.print(distanceRight);
  Serial.print(" cm");
  Serial.print(" Right Corner Distance: ");
  Serial.print(distanceRightCorner);
  Serial.print(" cm");
  Serial.print(" Left Corner Distance: ");
  Serial.print(distanceLeftCorner);
  Serial.println(" cm");

  
    if (distanceFront > 0 && distanceFront <= 60) {
    // Obstacle detected in front
    if (totalLeft < totalRight){
      // Obstacle detected on the left as well
      // Turn right
      steeringServo.write(0);
      digitalWrite(ren, HIGH);
      digitalWrite(len, LOW);
      analogWrite(rpwm, turnSpeed);
      analogWrite(lpwm, 0);
      delay(1250);}
     
    else if (totalRight < totalLeft) {
      // Obstacle detected on the right as well
      // Turn left
      steeringServo.write(180);
      digitalWrite(ren, HIGH);
      digitalWrite(len, LOW);
      analogWrite(rpwm, turnSpeed);
      analogWrite(lpwm, 0);
      delay(1250);
    } 
  }
  else {
    // No obstacle in front, move forward and steer straight
    steeringServo.write(92);
      digitalWrite(ren, HIGH);
      digitalWrite(len, LOW);
      analogWrite(rpwm, forwardSpeed);
      analogWrite(lpwm, 0);
    
  }

  if ( distanceRight <= 10 && distanceFront >= 60){
    steeringServo.write(135);
    digitalWrite(ren, HIGH);
    digitalWrite(ren, LOW);
    analogWrite(rpwm, forwardSpeed);
    analogWrite(lpwm, 0);
    delay (500);
  }

   if ( distanceLeft <= 10 && distanceFront >= 60){
    steeringServo.write(35);
    digitalWrite(ren, HIGH);
    digitalWrite(ren, LOW);
    analogWrite(rpwm, forwardSpeed);
    analogWrite(lpwm, 0);
    delay (500);
  }

  }
