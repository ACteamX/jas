#include <Servo.h>
Servo s;
int m1=4; int m2=9; 
int speed=6;

void setup() {
  s.attach(A8);
  pinMode(m1,OUTPUT);pinMode(m2,OUTPUT);pinMode(speed,OUTPUT);
}

void loop() {
digitalWrite(m1,1);digitalWrite(m2,0);analogWrite(speed,200);
delay(2000);

digitalWrite(m1,0);digitalWrite(m2,1);analogWrite(speed,200);
delay(2000);
/*
s.write(180);digitalWrite(m1,1);digitalWrite(m2,0);analogWrite(speed,200);
delay(2000);
s.write(90);digitalWrite(m1,0);digitalWrite(m2,0);analogWrite(speed,100);
delay(1000);
*/
}
