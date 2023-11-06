#include <Wire.h>

const int addr = 0x29; // I2C address of VL53L0X
const byte regAddr = 0x14; // Register address for reading distance

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(addr);
  Wire.write(0x00); // Write 0x00 to initiate VL53L0X
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(addr);
  Wire.write(regAddr);
  Wire.endTransmission(false);
  
  Wire.requestFrom(addr, 2); // Request 2 bytes of data
  int range = (Wire.read() << 8) | Wire.read();
  
  Serial.print("Distance: ");
  Serial.print(range);
  Serial.println(" mm");
  
  delay(500); // Delay between readings
}
