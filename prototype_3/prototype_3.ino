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
const int delay_start = 0; //3000;
boolean running = true;

const int intensity_off = 0;
const int intensity_0 = 10;
const int intensity_1 = 50;
const int intensity_2 = 100;
const int intensity_3 = 150;
const int intensity_4 = 200;
const int intensity_Connect_Floor_Low = 0;
const int intensity_Connect_Floor_High = 10;
const int intensity_Connect_Sofa_Low = 0;
const int intensity_Connect_Sofa_High = 20;
const int intensity_full = 255;
const int intensity_userHere = intensity_3;

const int intChange_1 = 5;

int state = 0; //0;
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
        delay(delay_start);
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
        setMatrixColorForIndex(34, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(42, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(42, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(35, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(34, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(35, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(43, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(51, intensity_userHere, intensity_userHere, intensity_userHere);
        break;

      case state_user1LuggageNotification :
        setMatrixColorForIndex(43, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(51, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_start);


        setMatrixColorForIndex(48, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(49, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(50, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(51, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(52, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(53, intensity_2, intensity_2, intensity_2);
        delay(delay_fade);
        setMatrixColorForIndex(40, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(41, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(42, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(43, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(44, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(45, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(46, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(48, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(49, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(50, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(51, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(52, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(53, intensity_1, intensity_1, intensity_1);
        delay(delay_fade);
        setMatrixColorForIndex(32, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(33, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(34, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(35, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(36, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(37, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(38, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(40, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(41, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(42, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(43, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(44, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(45, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(46, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(48, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(49, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(50, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(51, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(52, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(53, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(24, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(25, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(26, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(27, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(28, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(29, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(30, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(32, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(33, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(34, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(35, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(36, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(37, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(38, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(40, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(41, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(42, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(43, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(44, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(45, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(46, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(16, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(17, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(18, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(19, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(20, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(21, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(22, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(24, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(25, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(26, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(27, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(28, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(29, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(30, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(32, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(33, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(34, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(35, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(36, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(37, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(38, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(8, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(9, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(10, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(11, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(12, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(13, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(14, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(15, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(16, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(17, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(18, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(19, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(20, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(21, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(22, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(24, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(25, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(26, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(27, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(28, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(29, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(30, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(0, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(1, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(2, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(3, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(4, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(5, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(6, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(7, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(8, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(9, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(10, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(11, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(12, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(13, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(14, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(15, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(16, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(17, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(18, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(19, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(20, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(21, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(22, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(0, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(1, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(2, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(3, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(4, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(5, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(6, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(7, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(8, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(9, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(10, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(11, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(12, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(13, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(14, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(15, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(0, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(1, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(2, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(3, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(4, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(5, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(6, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(7, intensity_off, intensity_off, intensity_off);
        break;

      case state_user2ToWaiting :
        //delay(delay_start);
        setMatrixColorForIndex(43, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(51, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(24, intensity_userHere, intensity_userHere, intensity_userHere);
        // fade up sofa
        for (int a = intensity_off; a < intensity_3; a += intChange_1) {
          setLedMatrixSofaWithoutUser1(a, a, a);
          setMatrixColorForIndex(25, a, a, a);
          delay(delay_fade);
        }
        // fade down sofa
        for (int b = intensity_3; b > intensity_1; b -= intChange_1) {
          setLedMatrixSofaWithoutUser1(b, b, b);
          setMatrixColorForIndex(25, b, b, b);
          delay(delay_fade);
        }
        // fade up sofa 2
        for (int c = intensity_1; c < intensity_3; c += intChange_1) {
          setLedMatrixSofaWithoutUser1(c, c, c );
          setMatrixColorForIndex(25, c, c, c);
          delay(delay_fade);
        }
        // fade down sofa
        for (int d = intensity_3; d > intensity_off; d -= intChange_1) {
          setLedMatrixSofaWithoutUser1(d, d, d);
          setMatrixColorForIndex(25, d, d, d);
          delay(delay_fade);
        }
        delay(delay_standard);
        setMatrixColorForIndex(24, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(25, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(25, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(26, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(18, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(26, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(18, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(19, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(19, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(20, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(20, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(21, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(21, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(22, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(30, intensity_userHere, intensity_userHere, intensity_userHere);
        break;

      case state_user12Connect :
        setMatrixColorForIndex(43, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(51, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(22, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(30, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_start);
        for (int e = 0; e < 5; e++) {
          setMatrixColorForIndex(30, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          setMatrixColorForIndex(29, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          setMatrixColorForIndex(52, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High);
          setMatrixColorForIndex(44, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High);
          setMatrixColorForIndex(35, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          setMatrixColorForIndex(53, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High);
          setMatrixColorForIndex(36, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          setMatrixColorForIndex(21, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          delay(delay_fade);          
          setMatrixColorForIndex(38, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          setMatrixColorForIndex(37, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          setMatrixColorForIndex(46, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High);
          setMatrixColorForIndex(45, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High, intensity_Connect_Sofa_High);
          setMatrixColorForIndex(28, intensity_Connect_Floor_High, intensity_Connect_Floor_High, intensity_Connect_Floor_High);
          setMatrixColorForIndex(30, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          setMatrixColorForIndex(29, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          setMatrixColorForIndex(52, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low);
          setMatrixColorForIndex(44, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low);
          setMatrixColorForIndex(53, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low);
          setMatrixColorForIndex(36, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          setMatrixColorForIndex(21, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          setMatrixColorForIndex(35, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          delay(delay_fade);
          setMatrixColorForIndex(45, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low);
          setMatrixColorForIndex(38, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          setMatrixColorForIndex(37, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          setMatrixColorForIndex(46, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low, intensity_Connect_Sofa_Low);          
          setMatrixColorForIndex(28, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low, intensity_Connect_Floor_Low);
          setMatrixColorForIndex(30, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(29, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(52, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(44, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(53, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(36, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(35, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(21, intensity_off, intensity_off, intensity_off);
          delay(delay_fade);
          setMatrixColorForIndex(28, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(38, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(37, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(46, intensity_off, intensity_off, intensity_off);
          setMatrixColorForIndex(45, intensity_off, intensity_off, intensity_off);
          delay(delay_standard);
        }
        setMatrixColorForIndex(22, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(29, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(29, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(36, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(36, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(44, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(45, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(52, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(53, intensity_userHere, intensity_userHere, intensity_userHere);
        break;

      case state_user12LuggageNotification:
        setMatrixColorForIndex(43, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(51, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(44, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(45, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(52, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(53, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_start);


        setMatrixColorForIndex(48, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(49, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(50, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(51, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(52, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(53, intensity_2, intensity_2, intensity_2);
        delay(delay_fade);
        setMatrixColorForIndex(40, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(41, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(42, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(43, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(44, intensity_2, intensity_2, intensity_2);
        //setMatrixColorForIndex(45, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(46, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(48, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(49, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(50, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(51, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(52, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(53, intensity_1, intensity_1, intensity_1);
        delay(delay_fade);
        setMatrixColorForIndex(32, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(33, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(34, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(35, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(36, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(37, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(38, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(40, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(41, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(42, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(43, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(44, intensity_1, intensity_1, intensity_1);
        //setMatrixColorForIndex(45, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(46, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(48, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(49, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(50, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(51, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(52, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(53, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(24, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(25, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(26, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(27, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(28, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(29, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(30, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(32, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(33, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(34, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(35, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(36, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(37, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(38, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(40, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(41, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(42, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(43, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(44, intensity_off, intensity_off, intensity_off);
        //setMatrixColorForIndex(45, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(46, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(16, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(17, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(18, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(19, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(20, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(21, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(22, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(24, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(25, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(26, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(27, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(28, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(29, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(30, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(32, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(33, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(34, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(35, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(36, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(37, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(38, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(8, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(9, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(10, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(11, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(12, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(13, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(14, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(15, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(16, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(17, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(18, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(19, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(20, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(21, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(22, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(24, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(25, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(26, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(27, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(28, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(29, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(30, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(0, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(1, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(2, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(3, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(4, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(5, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(6, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(7, intensity_2, intensity_2, intensity_2);
        setMatrixColorForIndex(8, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(9, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(10, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(11, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(12, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(13, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(14, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(15, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(16, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(17, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(18, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(19, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(20, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(21, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(22, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(0, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(1, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(2, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(3, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(4, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(5, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(6, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(7, intensity_1, intensity_1, intensity_1);
        setMatrixColorForIndex(8, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(9, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(10, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(11, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(12, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(13, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(14, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(15, intensity_off, intensity_off, intensity_off);
        delay(delay_fade);
        setMatrixColorForIndex(0, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(1, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(2, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(3, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(4, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(5, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(6, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(7, intensity_off, intensity_off, intensity_off);
        break;

      case state_user12ToExit :
        setMatrixColorForIndex(43, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(51, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(44, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(45, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(52, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(53, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_start);



        setMatrixColorForIndex(43, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(51, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(44, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(45, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(52, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(53, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(35, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(36, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(37, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(35, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(36, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(37, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(29, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(28, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(27, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(29, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(28, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(27, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(21, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(20, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(19, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(21, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(20, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(19, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(13, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(12, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(11, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        setMatrixColorForIndex(13, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(12, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(11, intensity_off, intensity_off, intensity_off);
        setMatrixColorForIndex(5, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(4, intensity_userHere, intensity_userHere, intensity_userHere);
        setMatrixColorForIndex(3, intensity_userHere, intensity_userHere, intensity_userHere);
        delay(delay_standard);
        ledMatrixOff();
        break;

      default:
        ledMatrixOff();
        Serial.println(state);
        break;
    }
    running = false;
  }
}

void updateStatus(int s) {
  state += s;
  if (state_user12ToExit + 1 <= state || 0 > state) {
    state = state_idle;
  }
}
