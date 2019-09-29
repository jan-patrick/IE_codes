// button for now
// use I2C port

const int userPin_Entrance = 4;
const int userPin_Waiting = 2;
const int luggagePin = 6;

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
  pinMode(userPin_Entrance, INPUT);
  pinMode(userPin_Waiting, INPUT);
  pinMode(luggagePin, INPUT);
}

void getUseronEntrance() {
  if (1 == digitalRead(userPin_Entrance)) {
    entrance_State = true;
  }
}

void getUseronWaiting() {
  if (1 == digitalRead(userPin_Waiting)) {
    waiting_State = true;
  }
}

void getIfLuagge() {
  if (1 == digitalRead(luggagePin)) {
    luggage_State = true;
  } else {
    //luggage_State = false; // @Jan for now
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
  Serial.println(current_brainState);
  switch (current_brainState) {
    case brainState_idle :
      ledMatrixOff();
      ledOff();
      luggage_State = false; // @Jan for now
      break;
    case brainState_EntranceAndLuggage :
      setMatrixColorinRange(0, 32, 100, 100, 100);
      ledOff();
      Serial.println(findLuggageOfUser("Marie") + " found");
      waiting_State = false;
      break;
    case brainState_EntranceAndNoLuggage :
      ledMatrixOff();
      ledOn();
      waiting_State = false;
      break;
    case brainState_WaitingAndLuggage :
      setMatrixColorinRange(0, 32, 100, 100, 100);
      ledOff();
      Serial.println(findLuggageOfUser("John") + " found");
      entrance_State = false;
      break;
    case brainState_WaitingAndNoLuggage :
      ledMatrixOff();
      ledOff();
      entrance_State = false;
      break;
    default :
      Serial.println(current_brainState);
      break;
  }
}
