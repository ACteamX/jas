 int m1=13;
int m2=12;
int m3=11;
int m4=10;
char t;

void setup() {
  Serial.begin(9600);
  pinMode(m1,OUTPUT);pinMode(m2,OUTPUT);pinMode(m3,OUTPUT);pinMode(m4,OUTPUT);

}

void loop() {
  while(Serial.available()>0){
     t=Serial.read();
      Serial.println(t);
  }
  if(t=='F'){
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
  }
    if(t=='B'){
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
      if(t=='L'){
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,HIGH);
  }
      if(t=='R'){
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,HIGH);
    digitalWrite(m4,LOW);
  }
  
      if(t=='S'){
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
  }
  
}