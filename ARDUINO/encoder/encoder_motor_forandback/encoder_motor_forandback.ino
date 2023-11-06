// Motor control pins
#define IN1_PIN 18
#define IN2_PIN 17
#define PWM_PIN 16

// Encoder pins
#define ENCA 2 // Encoder Channel A (ENA) connected to Arduino's Pin 2
#define ENCB 3 // Encoder Channel B (ENB) connected to Arduino's Pin 3

// Variables
volatile int pulseCount = 0;         // Counter to store the number of pulses
unsigned long lastPulseTime = 0;    // Time of the last pulse count
float pulsesPerRevolution = 0;      // Number of pulses per revolution (calculated)

// Function declarations
void setMotorDirectionCW();
void setMotorDirectionCCW();
void setMotorSpeedCW(int speed);
void setMotorSpeedCCW(int speed);
void pulseCounter();

void setup() {
  Serial.begin(9600);
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), pulseCounter, CHANGE);
}

void loop() {
  // Rotate the motor in the clockwise direction for 2 seconds
  setMotorDirectionCW();   // Function to set motor direction for clockwise
  setMotorSpeedCW(200);    // Adjust speed from 0 to 255 (255 = full speed)
  delay(2000);             // Run the motor for 2 seconds
  float pulsesPerRevolutionCW = pulseCount / 2.0; // Assuming 2 pulses per revolution
 Serial.print("Pulses per Revolution CW: ");
  Serial.println(pulsesPerRevolutionCW);
 
  // Stop the motor
  setMotorSpeedCW(0);      // Set speed to 0
  delay(1000);             // Stop for 1 second

  // Calculate the pulses per revolution in the clockwise direction

  // Reset pulseCount for the next revolution calculation in the counterclockwise direction
  pulseCount = 0;

  // Rotate the motor in the counterclockwise direction for 2 seconds
  setMotorDirectionCCW();  // Function to set motor direction for counterclockwise
  setMotorSpeedCCW(200);   // Adjust speed from 0 to 255 (255 = full speed)
  delay(2000);             // Run the motor for 2 seconds
  float pulsesPerRevolutionCCW = pulseCount / 2.0; // Assuming 2 pulses per revolution

  // Print the pulses per revolution for both directions
  Serial.print("Pulses per Revolution CCW: ");
  Serial.println(pulsesPerRevolutionCCW);

  // Stop the motor
  setMotorSpeedCCW(0);     // Set speed to 0
  delay(1000);             // Stop for 1 second

  // Calculate the pulses per revolution in the counterclockwise direction

  // Reset pulseCount for the next loop iteration
  pulseCount = 0;
}

void setMotorDirectionCW() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
}

void setMotorDirectionCCW() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
}

void setMotorSpeedCW(int speed) {
  analogWrite(PWM_PIN, speed);
}

void setMotorSpeedCCW(int speed) {
  analogWrite(PWM_PIN, speed);
}

void pulseCounter() {
  // Read the current state of Encoder Channel B
  int b = digitalRead(ENCB);
  
  // Increment or decrement the pulseCount based on the state of Encoder Channel B
  if (b == HIGH) {
    pulseCount++;
  } else {
    pulseCount--;
  }
}
