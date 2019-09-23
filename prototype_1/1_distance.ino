// distance sensor one (time of flight)
// use I2C port

#include "Adafruit_VL53L0X.h"

int distance;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

unsigned long range_previousMillis = 0;

const long range_interval = 100;



// ---------------------------------------------- Distance sensors utility functions

void setupDistanceSensor() {
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  // power
  Serial.println(F("time of flight sensor loaded\n\n"));
}

void updateDistance() {
  distance = getDistance();
}

int getDistance() {
  unsigned long range_currentMillis = millis();

  //if (range_currentMillis - range_previousMillis >= range_interval) {
    //range_previousMillis = range_currentMillis;
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4 && 8000 >= measure.RangeMilliMeter && 0 <= measure.RangeMilliMeter) {  // phase failures have incorrect data
      return measure.RangeMilliMeter;
    } else {
      return -1;
    }
  //}
}
