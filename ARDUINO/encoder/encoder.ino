// Define motor driver connections
const int REN_PIN = 21; // Replace with the actual pin number you connect to REN
const int RPWM_PIN = 20; // Replace with the actual pin number you connect to RPWM
const int LEN_PIN = 18; // Replace with the actual pin number you connect to LEN
const int LPWM_PIN = 19; // Replace with the actual pin number you connect to LPWM

// Define encoder connections
const int encoderPinA = 2; // Replace with the actual pin number you connect to the encoder's yellow wire (output A)
const int encoderPinB = 3; // Replace with the actual pin number you connect to the encoder's green wire (output B)

volatile int encoderTicks = 0; // Used to store the encoder's position

void setup() {
  // Initialize motor control pins
  pinMode(RPWM_PIN, OUTPUT);
  pinMode(LPWM_PIN, OUTPUT);
  pinMode(REN_PIN, OUTPUT);
  pinMode(LEN_PIN, OUTPUT);

  // Initialize encoder pins and attach interrupt
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);

  // Start with motors disabled
  digitalWrite(REN_PIN, LOW);
  digitalWrite(LEN_PIN, LOW);
}

void loop() {
  // Example: Rotate the motor clockwise for 2 seconds
  moveClockwise();
  delay(2000);

  // Stop the motor
  stopMotor();
  delay(100);

  // Example: Rotate the motor counterclockwise for 2 seconds
  moveCounterclockwise();
  delay(2000);

  // Stop the motor
  stopMotor();
  delay(100);
}

void updateEncoder() {
  // Use this function to update the encoder position (when called by the interrupt)
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    encoderTicks++;
  } else {
    encoderTicks--;
  }
}

void moveClockwise() {
  digitalWrite(REN_PIN, HIGH);
  digitalWrite(LEN_PIN, LOW);
  analogWrite(LPWM_PIN, 0);
  analogWrite(RPWM_PIN, 255);
}

void moveCounterclockwise() {
  digitalWrite(REN_PIN, LOW);
  digitalWrite(LEN_PIN, HIGH);
  analogWrite(LPWM_PIN, 255);
  analogWrite(RPWM_PIN, 0);
}

void stopMotor() {
  digitalWrite(REN_PIN, LOW);
  digitalWrite(LEN_PIN, LOW);
  digitalWrite(RPWM_PIN, LOW);
  digitalWrite(LPWM_PIN, LOW);
}
