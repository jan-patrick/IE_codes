// Main program file for prototype 2 (luggage finding support)
//
// Uses (check the tabs of your Arduino window):
//   2_users.ino    - user detection
//   2_database.ino - for the user / luggage database
//   2_led.ino      - to highlight seating area
//   2_led-matrix   - for luggage highlighting
//   2_debug.ino    - for Serial and debugging
//
// Created September 2019
// By Jan Schneider

const int delay_standard = 500;
const int delay_waiting = delay_standard * 5;
boolean started = false;


void setup() {
  setupDebugging();
  //setupUserRec();
  //setupLed();
  setupLedMatrix();
}

void loop() {
  //getIfLuagge();
  //getUseronWaiting();
  //getUseronEntrance();
  //setBrainState();
  //mainFlow();
  if (!started) {
    started = true;
    setMatrixColorForIndex(5, 255, 255, 255);
    setMatrixColorForIndex(13, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(5, 0, 0, 0);
    setMatrixColorForIndex(13, 255, 255, 255);
    setMatrixColorForIndex(21, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(13, 0, 0, 0);
    setMatrixColorForIndex(21, 255, 255, 255);
    setMatrixColorForIndex(28, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(21, 0, 0, 0);
    setMatrixColorForIndex(28, 255, 255, 255);
    setMatrixColorForIndex(35, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(28, 0, 0, 0);
    setMatrixColorForIndex(35, 255, 255, 255);
    setMatrixColorForIndex(42, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(35, 0, 0, 0);
    setMatrixColorForIndex(42, 255, 255, 255);
    delay(delay_waiting);

    setMatrixColorForIndex(42, 255, 255, 255);
    setMatrixColorForIndex(35, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(42, 0, 0, 0);
    setMatrixColorForIndex(35, 255, 255, 255);
    setMatrixColorForIndex(28, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(35, 0, 0, 0);
    setMatrixColorForIndex(28, 255, 255, 255);
    setMatrixColorForIndex(21, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(28, 0, 0, 0);
    setMatrixColorForIndex(21, 255, 255, 255);
    setMatrixColorForIndex(22, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(21, 0, 0, 0);
    setMatrixColorForIndex(22, 255, 255, 255);
    setMatrixColorForIndex(23, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(22, 0, 0, 0);
    setMatrixColorForIndex(23, 255, 255, 255);
    delay(delay_standard);
    setMatrixColorForIndex(23, 0, 0, 0);
  }
}
