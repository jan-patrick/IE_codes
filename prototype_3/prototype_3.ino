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

boolean ledState = false;
unsigned long previousMillis = 0;
const long interval = 10000;


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
  for (int i = 0; i <= 57; i += 8) {
    if (0 < i) {
      setMatrixColorinRange(i - 8, i, 0, 0, 0);
    }
    setMatrixColorinRange(i, i + 8, 255, 255, 255);
    delay(1000);
  }
  ledMatrixOff();
}
