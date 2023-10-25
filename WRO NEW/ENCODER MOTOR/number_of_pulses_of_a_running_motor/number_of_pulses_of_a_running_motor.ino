#define ENCA 20 // YELLOW
#define ENCB 21 // WHITE
#define PWM 5
#define IN2 7
#define IN1 8

volatile long posi = 0; // Use long to accommodate larger position values

void setup() {
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  Serial.println("Car position calculation using encoder pulses...");
}

void loop() {
  // Run the motor continuously
  setMotor(1, 255, PWM, IN1, IN2);

  // Print the current position
  Serial.print("Current position: ");
  Serial.println(posi);
  
  // Add a delay to avoid overwhelming the serial monitor
  delay(100);
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}
