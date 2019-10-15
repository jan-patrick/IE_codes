// Main program file for prototype 2 (luggage finding support)
//
// Uses (check the tabs of your Arduino window):
//   2_users.ino    - user detection
//   2_database.ino - for the user / luggage database
//   2_led-matrix   - for luggage highlighting
//   2_debug.ino    - for Serial and debugging
//
// Created September 2019
// By Jan Schneider

const int delay_standard = 500;
const int delay_fade = 50;
const int delay_waiting = delay_standard * 5;
const int delay_start = 3000;
boolean running = true;

const int intensity_off = 0;
const int intensity_1 = 50;
const int intensity_2 = 100;
const int intensity_3 = 150;
const int intensity_4 = 200;
const int intensity_userHere = intensity_3;
const int intensity_full = 255;

const int intChange_1 = 5;

int state = 0;
const int state_idle = 0;
const int state_user1ToWaiting = 1;
const int state_user1LuggageNotification = 2;
const int state_user2ToWaiting = 3;
const int state_user12Connect = 4;
const int state_user12LuggageNotification = 5;
const int state_user12ToExit = 6;


void setup() {
  setupDebugging();
  setupUserRec();
  setupLedMatrix();
}

void loop() {
  if (getIfUser()) {
    updateStatus(1);
    running = true;
  }
  if (running) {
    switch (state) {
      case state_idle:
        ledMatrixOff();
        break;
      case state_user1ToWaiting:
        ledMatrixOff();
        //delay(delay_start);
        setMatrixColorForIndex(24, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        // fade up sofa
        for (int a = intensity_off; a < intensity_3; a += intChange_1) {
          setLedMatrixSofa(a, a, a);
          setMatrixColorForIndex(32, a, a, a);
          setMatrixColorForIndex(25, a, a, a);
          delay(delay_fade);
        }
        // fade down sofa
        for (int b = intensity_3; b > intensity_1; b -= intChange_1) {
          setLedMatrixSofa(b, b, b);
          setMatrixColorForIndex(32, b, b, b);
          setMatrixColorForIndex(25, b, b, b);
          delay(delay_fade);
        }
        // fade up sofa 2
        for (int c = intensity_1; c < intensity_3; c += intChange_1) {
          setLedMatrixSofa(c, c, c );
          setMatrixColorForIndex(32, c, c, c);
          setMatrixColorForIndex(25, c, c, c);
          delay(delay_fade);
        }
        // fade down sofa
        for (int d = intensity_3; d > intensity_off; d -= intChange_1) {
          setLedMatrixSofa(d, d, d);
          setMatrixColorForIndex(32, d, d, d);
          setMatrixColorForIndex(25, d, d, d);
          delay(delay_fade);
        }
        delay(delay_standard);
        setMatrixColorForIndex(24, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(25, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(33, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(25, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(33, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(26, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(34, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(42, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(42, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(26, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(35, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(34, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(35, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(43, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(51, intensity_userHere, intensity_userHere, intensity_userHere);

        break;
      case state_user1LuggageNotification :
        ledMatrixOff();
        //delay(delay_start);
        setMatrixColorForIndex(0, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        break;
      case state_user2ToWaiting :
        ledMatrixOff();
        //delay(delay_start);
        setMatrixColorForIndex(1, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        break;
      case state_user12Connect :
        ledMatrixOff();
        //delay(delay_start);
        setMatrixColorForIndex(2, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        break;
      case state_user12LuggageNotification:
        ledMatrixOff();
        //delay(delay_start);
        setMatrixColorForIndex(3, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        break;
      case state_user12ToExit :
        ledMatrixOff();
        //delay(delay_start);
        setMatrixColorForIndex(4, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        break;


      default:
        Serial.println(state);
        break;
    }
    running = false;
  }
}

void updateStatus(int s) {
  state += s;
  if (state_user12ToExit + 1 <= state) {
    state = state_idle;
  }
}
