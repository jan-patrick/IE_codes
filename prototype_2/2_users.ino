// Ultrasonic Rangers


#include "Ultrasonic.h"
unsigned long previousMillis_userEntrance = 0;
unsigned long previousMillis_userWaiting = 0;
unsigned long previousMillis_luggage = 0;
const long interval_ultrasonic = 250;

// in cm
const long range_userEntrance = 5;
const long range_userWaiting = 5;
const long range_luggage = 300;

Ultrasonic user_Entrance(4);
Ultrasonic user_Waiting(3);
const int luggage = A3;

boolean entrance_State = false;
boolean waiting_State = false;
boolean luggage_State = false;

int previous_brainState = -1;
int current_brainState = 0;
const int brainState_idle = 0;
const int brainState_EntranceAndLuggage = 1;
const int brainState_EntranceAndNoLuggage = 2;
const int brainState_WaitingAndLuggage = 3;
const int brainState_WaitingAndNoLuggage = 4;

// ---------------------------------------------- Distance sensors utility functions

void setupUserRec() {

}

void getUseronEntrance() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_userEntrance >= interval_ultrasonic) {
    previousMillis_userEntrance = currentMillis;
    long RangeInCentimeters;
    RangeInCentimeters = user_Entrance.MeasureInCentimeters();
    if (range_userEntrance >= RangeInCentimeters) {
      entrance_State = true;
    } else {
      entrance_State = false;
    }
  }
}

void getUseronWaiting() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_userWaiting >= interval_ultrasonic) {
    previousMillis_userWaiting = currentMillis;
    long RangeInCentimeters;
    RangeInCentimeters = user_Waiting.MeasureInCentimeters();
    if (range_userWaiting >= RangeInCentimeters) {
      waiting_State = true;
    } else {
      waiting_State = false;
    }
  }
}

void getIfLuagge() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_luggage >= interval_ultrasonic) {
    previousMillis_luggage = currentMillis;
    int sensorValue = analogRead(luggage);
    //Serial.println(sensorValue);
    if (range_luggage <= sensorValue) {
      luggage_State = true;
    } else {
      luggage_State = false;
    }
  }
}

void setBrainState() {
  // user at entrance
  if (entrance_State) {
    // if luggage there
    if (luggage_State) {
      current_brainState = brainState_EntranceAndLuggage;
      // if no luggage
    } else {
      current_brainState = brainState_EntranceAndNoLuggage;
    }
    // user at waiting area
  } else if (waiting_State) {
    // if luggage there
    if (luggage_State) {
      current_brainState = brainState_WaitingAndLuggage;
      // if no luggage
    } else {
      current_brainState = brainState_WaitingAndNoLuggage;
    }
    // if no user there
  } else {
    current_brainState = brainState_idle;
  }
  previous_brainState = current_brainState;
}

void mainFlow() {
  //Serial.println(current_brainState);
  switch (current_brainState) {
    case brainState_idle :
      ledMatrixOff();
      ledOff();
      break;
    case brainState_EntranceAndLuggage :
      setMatrixColorinRange(0, 32, 100, 100, 100);
      ledOff();
      //Serial.println(findLuggageOfUser("Marie") + " found");
      break;
    case brainState_EntranceAndNoLuggage :
      ledMatrixOff();
      ledOn();
      break;
    case brainState_WaitingAndLuggage :
      setMatrixColorinRange(0, 32, 100, 100, 100);
      ledOff();
      //Serial.println(findLuggageOfUser("John") + " found");
      break;
    case brainState_WaitingAndNoLuggage :
      ledMatrixOff();
      ledOn50Percent();
      break;
    default :
      Serial.println(current_brainState);
      break;
  }
}
