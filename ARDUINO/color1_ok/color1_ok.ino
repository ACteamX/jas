#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define OUT 12

// Reference colors
const int redRef[] = {200, 80, 80};    // Red (adjust these values based on your calibration)
const int greenRef[] = {80, 150, 80};  // Green (adjust these values based on your calibration)
const int blueRef[] = {80, 80, 150};   // Blue (adjust these values based on your calibration)

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
}

void loop() {
  int redValue = getColorValue(2);    // Red color
  int greenValue = getColorValue(1);  // Green color
  int blueValue = getColorValue(0);   // Blue color

  // Print the RGB values
  Serial.print("Red: ");
  Serial.print(redValue);
  Serial.print(" Green: ");
  Serial.print(greenValue);
  Serial.print(" Blue: ");
  Serial.println(blueValue);

  // Match the color based on the reference colors
  String color = matchColor(redValue, greenValue, blueValue);

  // Print the matched color
  Serial.print("Matched Color: ");
  Serial.println(color);

  delay(1000);
}

int getColorValue(int color) {
  digitalWrite(S2, color & 0x01);
  digitalWrite(S3, (color >> 1) & 0x01);

  // Read the color value
  int value = pulseIn(OUT, LOW);

  return value;
}

String matchColor(int red, int green, int blue) {
  int redDistance = calculateColorDistance(red, green, blue, redRef[0], redRef[1], redRef[2]);
  int greenDistance = calculateColorDistance(red, green, blue, greenRef[0], greenRef[1], greenRef[2]);
  int blueDistance = calculateColorDistance(red, green, blue, blueRef[0], blueRef[1], blueRef[2]);

  // Determine the minimum distance and match the color
  if (redDistance < greenDistance && redDistance < blueDistance)
    return "Red";
  else if (greenDistance < redDistance && greenDistance < blueDistance)
    return "Green";
  else if (blueDistance < redDistance && blueDistance < greenDistance)
    return "Blue";
  else
    return "Unknown";
}

int calculateColorDistance(int r1, int g1, int b1, int r2, int g2, int b2) {
  // Calculate the Euclidean distance between two colors
  int dr = r2 - r1;
  int dg = g2 - g1;
  int db = b2 - b1;
  return dr * dr + dg * dg + db * db;
}
