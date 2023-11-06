#include <Servo.h>
Servo servo;
int count=0;
// Color Sensor Pins
#define S0 22
#define S1 23
#define S2 24
#define S3 25
#define sensorOut 26

// Variables for color detection
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

//ir sensor
const int IR1=30; const int IR2=31;

void setup() {
  Serial.begin(9600);
  servo.attach(A7);
  // Color Sensor Initialization
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
 
  //
  pinMode(IR1,INPUT);  pinMode(IR2,INPUT);
}

void loop() {
  // Checking RED
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redValue = pulseIn(sensorOut, LOW);

  // Checking GREEN
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenValue = pulseIn(sensorOut, LOW);

  // Checking BLUE
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  blueValue = pulseIn(sensorOut, LOW);
  // Print color readings
  Serial.print("R=");
  Serial.print(redValue);
  Serial.print(" G=");
  Serial.print(greenValue);
  Serial.print(" B=");
  Serial.print(blueValue);

  delay(1000); // Adjust the delay as needed
/*
  if((redValue+greenValue+blueValue)<=385){
  Serial.println("= Green");}

  if((redValue+greenValue+blueValue)>=395){
  Serial.println("= RED");}
*/

if(redValue+greenValue+blueValue>=1000){
count++;
}
Serial.print(" count");
Serial.println(count);
}
