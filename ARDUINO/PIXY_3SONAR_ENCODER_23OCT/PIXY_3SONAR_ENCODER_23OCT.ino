#include <Servo.h>

#include <Pixy2.h>
Pixy2 pixy;

//sonar sensors
const int TRIGGER_PIN_FRONT = 36;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 37;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = 38;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 39;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = 40;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 41;     // Right sonar sensor echo pin

const int motor1 = 4;
const int motor2 = 9;
const int pwm = 6;
//encoder
const int ENCA = 20; // Encoder pulse input A
const int ENCB = 21; // Encoder pulse input B

Servo steeringServo;

const int forwardSpeed = 150; // Adjust this value for the desired forward speed
const int turnSpeed = 130;    // Adjust this value for the desired turn speed

volatile long posi = 0; // Use long to accommodate larger position values

//red and green LEDs pins
int red=52;
int green=53;

void setup() {
  Serial.begin(9600);
  steeringServo.attach(19);
  //pixy
   pixy.init();
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
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

int blocks = pixy.ccc.getBlocks();

  int largestArea = 0;  // Variable to track the largest area
  int closestColor = -1;  // Variable to track the color closest to the camera
  int closestWidth = 0;  // Variable to track the width of the closest color
  int closestHeight = 0;  // Variable to track the height of the closest color
  int closestX = 0;  // Variable to track the X coordinate of the closest color
  int closestY = 0;  // Variable to track the Y coordinate of the closest color

  for (int i = 0; i < blocks; i++) {
    int area = pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height;

    // Compare areas to determine the color closest to the camera
    if (area > largestArea) {
      largestArea = area;
      closestColor = pixy.ccc.blocks[i].m_signature;
      closestWidth = pixy.ccc.blocks[i].m_width;
      closestHeight = pixy.ccc.blocks[i].m_height;
      closestX = pixy.ccc.blocks[i].m_x;
      closestY = pixy.ccc.blocks[i].m_y;
    }
  }

  //green and red LEDs and off
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  //
if (closestColor == 2) {
    Serial.print("Green obstacle detected. ");
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
      steeringServo.write(135);
      moveForward(turnSpeed);
      delay(80);  
        if (distanceLeft<=26){    
      steeringServo.write(60);
      moveForward(turnSpeed);
      delay(100);
    }
    
    } 
    else if (closestColor == 1) {
    Serial.print("Red obstacle detected. ");
    digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
    steeringServo.write(60);
      moveForward(turnSpeed);
      delay(80);
    
    if (distanceRight<=26){    
      steeringServo.write(120);
      moveForward(turnSpeed);
      delay(100);
    }
  }

  // Stop the car if pulse count is greater than 34000
  if (posi > 99000 && posi < 1020000 ) {
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    analogWrite(pwm, 0);
    Serial.println("Car stopped");
    while (true);  // This will halt the program and effectively stop the car
  }

  // Implement obstacle avoidance based on sensor readings
  if (distanceFront >= 0 && distanceFront <= 70 && closestColor != 2 && closestColor != 1) {
    // Obstacle avoidance logic
    if ( distanceRight>distanceLeft) {
     
      steeringServo.write(50);
      moveForward(turnSpeed);
      delay(250);
    } else if ( distanceLeft>distanceRight) {
     
      steeringServo.write(140);
      moveForward(turnSpeed);
      delay(250);
    }
  } else {
    moveForward(forwardSpeed);
    steeringServo.write(95);
  }

  if (distanceFront >= 40 && closestColor != 2 && closestColor != 1) {
    // Obstacle avoidance logic when distanceFront is greater than or equal to 40
    if ( distanceRight > distanceLeft ) {
      steeringServo.write(80);
      moveForward(turnSpeed);
      delay(10);
    }
    if ( distanceLeft > distanceRight ) {
      steeringServo.write(110);
      moveForward(turnSpeed);
      delay(10);
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
void moveBack(int speed) {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
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
