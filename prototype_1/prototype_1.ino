// Main program file for prototype 1
//
// Uses (check the tabs of your Arduino window):
//   1_distance.ino - for the distance sensor
//   1_leds.ino     - to create led animations
//   1_debug.ino    - for Serial and debugging
//
// Created September 2019
// By Jan Schneider


const boolean debug = true;

void setup() {
  setupDebugging();
  setupDistanceSensor();
  setupLeds();
}

void loop() {
  //setMatrixColor(200, 100, 100);
  updateDistance();
  setLedStatus();
}
