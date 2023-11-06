#include <Wire.h>
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int numReadings = 5; // Number of readings to average
int readings[numReadings]; // Store the readings
int index = 0;             // Index of the current reading
int total = 0;             // Total of the readings

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  
  // Initialize readings array to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {  // 4 = Phase out of valid range
    total = total - readings[index];   // Subtract the oldest reading
    readings[index] = measure.RangeMilliMeter; // Store the new reading
    total = total + readings[index];   // Add the new reading
    index = (index + 1) % numReadings; // Move to the next index

    int averageDistance = total / numReadings; // Calculate the average

    Serial.print(F("Average Distance (mm): "));
    Serial.println(averageDistance);
  } else {
    Serial.println(F("Out of range"));
  }

  delay(100);
}
