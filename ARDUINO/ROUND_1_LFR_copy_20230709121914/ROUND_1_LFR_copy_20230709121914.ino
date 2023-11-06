// motors
const int in1=2;
const int in2=4;
const int in3=5;
const int in4=7;
const int enA=3;
const int enB=6;

// IR SENSORS
const int IR1=13;//LSA
const int IR2=12;//LS
const int IR3=11;//CS
const int IR4=10;//LSB
const int IR5=9;//RSB

// speed
const int fs=180; // forward speed
const int ts=110; //turn speed
const int bs=50; // back speed

 void setup(){
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  //SENSORS
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(IR3,INPUT);
  pinMode(IR4,INPUT);
  pinMode(IR5,INPUT);

 }
void loop(){
  int LSA=digitalRead(IR1); 
  int LSB=digitalRead(IR2); 
  int CS=digitalRead(IR3);
   int RSA=digitalRead(IR4);
    int RSB=digitalRead(IR5);
  
       

if(LSB==0 && LSA==0 && CS==1 && RSA==0 && RSB==0){ // forward
digitalWrite(in1,HIGH);  
digitalWrite(in2,LOW);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(enA,fs);
analogWrite(enB,fs);

}
// MOVING RIGHT USING RIGHT SENSORS
if(LSB==0 && LSA==0 && CS==0 && RSA==1 && RSB==0){ // right
digitalWrite(in1,LOW);  
digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(enA,bs  );
analogWrite(enB,ts);}
if(LSB==0 && LSA==0 && CS==1 && RSA==1 && RSB==0){ // right
digitalWrite(in1,LOW);  
digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(enA,bs);
analogWrite(enB,ts);}
if(LSB==0 && LSA==0 && CS==0 && RSA==0 && RSB==1){ //right
digitalWrite(in1,LOW);  
digitalWrite(in2,HIGH);
digitalWrite(in3,HIGH);
digitalWrite(in4,LOW);
analogWrite(enA,bs);
analogWrite(enB,ts);}


// moving left now,,using the left sensors

if(LSB==0 && LSA==1 && CS==0 && RSA==0 && RSB==0){ // LEFT
digitalWrite(in1,HIGH);  
digitalWrite(in2,LOW);

digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
analogWrite(enA,ts);
analogWrite(enB,bs);}

if(LSB==0 && LSA==1 && CS==1 && RSA==0 && RSB==0){ // LEFT
digitalWrite(in1,HIGH);  
digitalWrite(in2,LOW);

digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
analogWrite(enA,ts);
analogWrite(enB,bs);}


if(LSB==1 && LSA==0 && CS==0 && RSA==0 && RSB==0){ // LEFT
digitalWrite(in1,HIGH);  
digitalWrite(in2,LOW);

digitalWrite(in3,LOW);
digitalWrite(in4,HIGH);
analogWrite(enA,ts);
analogWrite(enB,bs);}
}
