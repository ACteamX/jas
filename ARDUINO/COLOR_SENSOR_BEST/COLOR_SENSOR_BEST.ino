#include <Wire.h>

// Color Sensor Pins
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12

// Ultrasonic Sensor Pins
#define trigPin 2
#define echoPin 3

// Variables for color detection
int redFrequency = 0;
int greenFrequency = 0;

// Variables for distance
long duration;
int distance;

// Threshold to determine the dominant color
const int colorThreshold = 50;

void setup() {
  Serial.begin(9600);
  
  // Color Sensor Initialization
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  // Ultrasonic Sensor Initialization
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Turn on the white LED to illuminate the object
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void loop() {
  // Check Distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  delay(1000);
  // Checking RED
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    redFrequency = pulseIn(sensorOut, LOW);
  
    // Checking GREEN
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    greenFrequency = pulseIn(sensorOut, LOW);

    // Print color readings
    Serial.print("R=");
    Serial.print(redFrequency);
    Serial.print(" G=");
    Serial.println(greenFrequency);
/*
    // Determine the dominant color
    if (abs(redFrequency+greenFrequency) >=950 && redFrequency>=445 && greenFrequency>=500){
      Serial.println("RED");
    } else if (redFrequency+greenFrequency >=930 && redFrequency>=445 && greenFrequency>=500) {
      Serial.println("GREEN");
      // Take appropriate action for Red dominance
    } 
*/
  delay(500);
}
