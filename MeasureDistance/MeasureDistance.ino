#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

Servo servo;
VL53L0X sensor;
int distance = 0;
int distMax = 1;

void setup() {
  servo.attach(3);

  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor.startContinuous();
}

void loop() {
  distance = sensor.readRangeContinuousMillimeters();
  Serial.print(distance);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();
  distMax = max(distance, distMax);

  int angle = map(distance, 0, distMax, 0, 180);
  servo.write(angle);
  delay(15);
}
