#define ENCA 20 // YELLOW
#define ENCB 21 // WHITE
#define PWM 5
#define IN2 7
#define IN1 8

volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;
unsigned long startTime = 0;
const unsigned long duration = 1000;  // Run the motor for 10 seconds

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  Serial.println("Motor running for 10 seconds, counting pulses...");
  startTime = millis();  // Record the start time
}

void loop() {
  // Check if 10 seconds have passed
  if (millis() - startTime < duration) {
    // Run the motor in one direction
    setMotor(1, 255, PWM, IN1, IN2);
  } else {
    // Stop the motor and print the pulse count
    setMotor(0, 0, PWM, IN1, IN2);
    Serial.print("Pulses count: ");
    Serial.println(posi);
    while (true) {
      // Do nothing, just stay in this loop to halt the program
    }
  }
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
