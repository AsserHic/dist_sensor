#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

#define MAX_READ 8190

Servo servo;
VL53L0X sensor;
int distance = 0;
int distMax = 1;

void setup() {
  servo.attach(3);

  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init()) {
    while (1) {}  // TODO: blink!
  }

  sensor.startContinuous();
}

void loop() {
  distance = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) {
    servo.write(0);
  }
  if (distance >= MAX_READ) {
    distance = distMax;
  } else {
    distMax = max(distance, distMax);
  }

  int angle = map(distance, 0, distMax, 0, 180);
  servo.write(angle);
  delay(15);
}
