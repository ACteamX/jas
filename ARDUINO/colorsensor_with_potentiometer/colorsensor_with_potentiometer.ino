// Variables for color detection
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read the analog inputs for red, green, and blue
  redValue = analogRead(A0);
  greenValue = analogRead(A1);
  blueValue = analogRead(A2);

  // Print color readings
  Serial.print("R=");
  Serial.print(redValue);
  Serial.print(" G=");
  Serial.print(greenValue);
  Serial.print(" B=");
  Serial.println(blueValue);

  // Determine the dominant color based on the thresholds
  const int redThreshold = 100;
  const int greenThreshold = 100;
  const int blueThreshold = 100;

  if (redValue >= redThreshold && greenValue < greenThreshold && blueValue < blueThreshold) {
    Serial.println("Red");
    // Take appropriate action for Red dominance
  } else if (greenValue >= greenThreshold && redValue < redThreshold && blueValue < blueThreshold) {
    Serial.println("Green");
    // Take appropriate action for Green dominance
  } else if (blueValue >= blueThreshold && redValue < redThreshold && greenValue < greenThreshold) {
    Serial.println("Blue");
    // Take appropriate action for Blue dominance
  } else {
    Serial.println("Uncertain: Cannot determine the dominant color.");
  }

  delay(500);
}
