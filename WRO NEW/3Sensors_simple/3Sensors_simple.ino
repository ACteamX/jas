#include <Servo.h>

const int TRIGGER_PIN_FRONT =36;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 37;     // Front sonar sensor echo pin
const int TRIGGER_PIN_LEFT = 38;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 39;     // Left sonar sensor echo pin
const int TRIGGER_PIN_RIGHT = 40;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 41;     // Right sonar sensor echo pin


const int motor1 = 4;const int motor2 =9;const int pwm=6;
Servo steeringServo;

const int forwardSpeed = 150; // Adjust this value for the desired forward speed
const int turnSpeed = 130;     // Adjust this value for the desired turn speed  

void setup(){
  Serial.begin(9600);
  steeringServo.attach(A8);
  // Motor
  pinMode(motor1, OUTPUT);pinMode(pwm, OUTPUT);pinMode(motor2, OUTPUT);
  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT);pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);pinMode(ECHO_PIN_RIGHT, INPUT);}

int getAverageDistance(int triggerPin, int echoPin, int numSamples) {
  long totalDistance = 0;
  for (int i = 0; i < numSamples; i++) {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
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

    sumFront += distanceFront;
    sumLeft += distanceLeft;
    sumRight += distanceRight;}
  int averageFront = sumFront / numSamples;
  int averageLeft = sumLeft / numSamples;
  int averageRight = sumRight / numSamples;


  Serial.print("Front: ");
  Serial.print(averageFront);
  Serial.print(" cm,Left: ");
  Serial.print(averageLeft);
  Serial.print(" cm,Right: ");
  Serial.print(averageRight);
  Serial.println(" cm");
    }
