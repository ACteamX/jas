#include "Adafruit_VL53L0X.h"


// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
int distanceLeft, distanceRight;

// set the pins to shutdown
#define SHT_LOX1 11
#define SHT_LOX2 12

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;


void read_dual_sensors() {
  int distanceLeft, distanceRight;
  lox1.rangingTest(&measure1, false);  // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false);  // pass in 'true' to get debug data printout!
  // print sensor one reading
  if (measure1.RangeStatus != 4) {  // if not out of range
    distanceLeft = measure1.RangeMilliMeter / 10;
    Serial.print("left");
    Serial.print(distanceLeft);

  } else {
    return 800;
  }
  // print sensor two reading
  if (measure2.RangeStatus != 4) {
    distanceRight = measure2.RangeMilliMeter / 10;
    Serial.print(" right:");
    Serial.println(distanceRight);
  } else {
    return 800;
  }
}
void tof_setup() {
  // wait until serial port opens for native USB devices
  while (!Serial) { delay(1); }
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  Serial.println("Shutdown pins inited...");
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);

  Serial.println("Both in reset mode...(pins are low)");
  Serial.println("Starting...");


  // all reset
  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  // initing LOX1
  if (!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while (1)
      ;
  }
  delay(10);
  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  //initing LOX2
  if (!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while (1)
      ;
  }
}

void setup() {
  Serial.begin(9600);
  tof_setup();
}

void loop() {
  read_dual_sensors();
  delay(10);
}
