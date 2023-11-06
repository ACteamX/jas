#define ENCA 20 // YELLOW
#define ENCB 21 // WHITE
#define PWM 5
#define IN2 7
#define IN1 8

volatile long posi = 0; // Use long to accommodate larger position values
volatile unsigned long prevMillis = 0;
float pulsesPerUnitDistance = 0;
float knownDistance = 10.0;  // Known distance to move for calibration
bool calibrationDone = false;  // Flag to indicate if calibration is done

void setup() {
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
  
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  Serial.println("Car position calculation using encoder pulses and adaptive control...");
  
  // Calibrate pulses per unit distance
  calibratePulsesPerUnitDistance();
}

void loop() {
  // Run the motor if calibration is done
  if (calibrationDone) {
    // Run the motor continuously
    setMotor(1, 255, PWM, IN1, IN2);

    // Print the current position
    Serial.print("Current position: ");
    Serial.println(posi);
  } else {
    // Stop the motor during calibration
    setMotor(0, 0, PWM, IN1, IN2);
  }
  
  // Add a delay to avoid overwhelming the serial monitor
  delay(100);
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2) {
  analogWrite(pwm, pwmVal);

  // Update motor direction correctly
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

void calibratePulsesPerUnitDistance() {
  Serial.println("Calibrating pulses per unit distance...");
  Serial.println("Move the car a known distance, then type 'calibrate' and press Enter.");

  // Start the motor
  setMotor(1, 255, PWM, IN1, IN2);

  while (!Serial.available()) {
    // Wait for user input
  }

  // Stop the motor
  setMotor(0, 0, PWM, IN1, IN2);

  // Wait for the user to type 'calibrate'
  String userInput = Serial.readStringUntil('\n');
  userInput.trim();
  
  if (userInput.equals("calibrate")) {
    // Calculate pulses per unit distance
    pulsesPerUnitDistance = (float) posi / knownDistance;
    Serial.print("Pulses per unit distance: ");
    Serial.println(pulsesPerUnitDistance);
  } else {
    Serial.println("Invalid input. Calibration aborted.");
  }
}
