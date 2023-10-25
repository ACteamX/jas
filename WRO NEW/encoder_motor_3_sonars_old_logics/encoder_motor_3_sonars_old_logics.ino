#define TRIGGER_PIN 40  // Connect the trigger pin of the sensor to Arduino digital pin 2
#define ECHO_PIN 41    // Connect the echo pin of the sensor to Arduino digital pin 3

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Trigger the sensor by sending a 10us pulse
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Read the pulse duration on the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters using the speed of sound
  // (speed of sound is approximately 343 meters per second or 0.0343 cm/microsecond)
  float distance_cm = duration * 0.0343 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Delay before taking the next reading
  delay(100); // Adjust the delay as needed
}
