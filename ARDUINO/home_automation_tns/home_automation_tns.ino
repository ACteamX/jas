#include<Servo.h>
Servo s;

const int d1 = 5;const int d2 = 13;
const int d3 = 7;const int d4 = 8;

const int d5 = 2;//AC DEVICE RELAY

const int d6 = 10;
const int d7 = 11;
const int d8 = 12;//gate

void setup() {
pinMode(d1, OUTPUT);pinMode(d2, OUTPUT); pinMode(d3, OUTPUT); pinMode(d4, OUTPUT); 
pinMode(d5, OUTPUT); pinMode(d6, OUTPUT); pinMode(d7, OUTPUT); pinMode(d8, OUTPUT);  
//sensor
s.attach(6);
  //all are on when powered on
digitalWrite(d1, HIGH);digitalWrite(d2, HIGH);digitalWrite(d3, HIGH);digitalWrite(d4, HIGH);
digitalWrite(d5, HIGH);digitalWrite(d6, HIGH);digitalWrite(d7, HIGH);digitalWrite(d8, HIGH); 
Serial.begin(9600);}



void loop() {



  if (Serial.available() > 0) {
  char t = Serial.read();
  //device 01
  if (t == 'A') {digitalWrite(d1, HIGH);} 
  else if (t == 'a') {digitalWrite(d1, LOW);}
  //device 02
  if (t == 'B') {digitalWrite(d2, HIGH);} 
  else if (t == 'b') {digitalWrite(d2, LOW);}
  //device 03
  if (t == 'C') {digitalWrite(d3, HIGH);} 
  else if (t == 'c') {digitalWrite(d3, LOW);}
  //device 04
  if (t == 'D') {digitalWrite(d4, HIGH);} 
  else if (t == 'd') {digitalWrite(d4, LOW);}
  //device 05
  if (t == 'E') {digitalWrite(d5, HIGH);} 
  else if (t == 'e') {digitalWrite(d5, LOW);}
  //device 06
  if (t == 'F') {digitalWrite(d6, HIGH);}
  else if (t == 'f') {digitalWrite(d6, LOW);}
  //device 07
  if (t == 'G') {digitalWrite(d8, HIGH);} 
  else if (t == 'g') {digitalWrite(d8, LOW);}
  //device 08
  if (t == 'H') {s.write(110);delay(500);
  } 
  else if (t == 'h') {s.write(0);delay(100);}

  }
}