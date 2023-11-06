#include <Wire.h>
#include <MPU6050_light.h>
#include <SimpleKalmanFilter.h>

MPU6050 mpu(Wire);
SimpleKalmanFilter kalmanFilter(2, 2, 0.01);  // e_mea, e_est, q

unsigned long previousMillis = 0;
const long interval = 5;                          // Set your desired interval here (5 milliseconds in this case)
const unsigned long sensorResetInterval = 10000;  // Reset the sensor every 10 seconds
float initialvalue = 0;
float deviation = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.begin();
  mpu.update();

  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // Stop if unable to connect to MPU6050

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();  // Calibrate MPU6050
  Serial.println("Done!\n");
  initialvalue = mpu.getAngleZ();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= sensorResetInterval) {
    mpu.begin();                     // Re-initialize the MPU6050 to emulate a soft reset
    delay(1000);                     // Wait for the sensor to initializex
    previousMillis = currentMillis;  // Reset the timer
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    mpu.update();

    float gyroZ = mpu.getAngleZ();

    float filteredValue = kalmanFilter.updateEstimate(gyroZ);
    deviation = filteredValue - initialvalue;

    Serial.print("Gyro Z (raw): ");
    Serial.print(gyroZ);

    Serial.print("\tFiltered Gyro Z: ");
    Serial.print(filteredValue);

    Serial.print("\tintial Value: ");
    Serial.print(initialvalue);

    Serial.print("\tdeviation: ");
    Serial.println(deviation);
  }
}
