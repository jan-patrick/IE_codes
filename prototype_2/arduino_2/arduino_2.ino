// Main program file for prototype 2
//
// Uses (check the tabs of your Arduino window):
//   2_led_matrix.ino   - for controling led matrix
//   2_led_single.ino   - the single led
//   2_debug.ino        - for Serial and debugging
//
// Created September 2019
// By Jan Schneider


const boolean debug = true;

void setup() {
  setupDebugging();
  setupMatrix();
  setupLed();
}

void loop() {
  setMatrixColor(0,0,0);
  ledOff();
}
