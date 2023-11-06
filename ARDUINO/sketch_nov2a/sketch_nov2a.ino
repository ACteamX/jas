const int TRIGGER_PIN_FRONT = A2;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = A3;     // Front sonar sensor echo pin

const int TRIGGER_PIN_LEFT = A0;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = A1;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT = A4;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = A5;     // Right sonar sensor echo pin

//
int L1=2; int L2=3;int R1=4; int R2=5; 
int speedL=9;int speedR=10;

const int forwardSpeed = 120;
const int turnSpeed = 130; 
const int backSpeed = 70; 

void setup() {
  Serial.begin(9600);

  // Motor
  pinMode(L1, OUTPUT); pinMode(L2, OUTPUT); pinMode(R1, OUTPUT); pinMode(R2, OUTPUT);
  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT); pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT); pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT); pinMode(ECHO_PIN_RIGHT, INPUT);
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
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


  if (distanceFront >10 && distanceFront <= 60){
     digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(R1, LOW);
      digitalWrite(R2, LOW);
      analogWrite(speedL,turnSpeed);
      analogWrite(speedR, backSpeed);
      delay(200);
  if (distanceRight > distanceLeft ) {
    // Obstacle detected on the left as well
    // Turn right
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      analogWrite(speedL,turnSpeed);
      analogWrite(speedR, backSpeed);
      delay(200);
}
  if (distanceLeft > distanceRight   ) {
    // Obstacle detected on the right as well
    // Turn left
          digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      analogWrite(speedL,backSpeed);
      analogWrite(speedR, turnSpeed);
      delay(300);  
    
      }}
else if(distanceFront<=12){
         digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      analogWrite(speedL,backSpeed);
      analogWrite(speedR, backSpeed);
      delay(100);
      }
      
else{
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(R1,HIGH);
      digitalWrite(R2, LOW);
      analogWrite(speedL,forwardSpeed);
      analogWrite(speedR, forwardSpeed);

}
/*

  if (distanceFront >=0 && distanceFront >= 40){
  if (distanceRight >distanceLeft  ) {
    // Obstacle detected on the left as well
    // Turn left
      digitalWrite(L1, HIGH);
      digitalWrite(L2, LOW);
      digitalWrite(R1, LOW);
      digitalWrite(R2, HIGH);
      analogWrite(speedL,turnSpeed);
      analogWrite(speedR, backSpeed);
      delay(20);  }
  if (distanceLeft >distanceRight   ) {
      digitalWrite(L1, LOW);
      digitalWrite(L2, HIGH);
      digitalWrite(R1, HIGH);
      digitalWrite(R2, LOW);
      analogWrite(speedL,backSpeed);
      analogWrite(speedR,turnSpeed);
      delay(20);
      }
  }
*/
}