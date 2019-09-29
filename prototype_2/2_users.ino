// button for now
// use I2C port

const int userPin_Entrance = 4;
const int userPin_Waiting = 6;
const int luggagePin = 2;

boolean entrance_State = false;
boolean waiting_State = false;
boolean luggage_State = false;

int current_brainState = 0;
int brainState_idle = 0;
int brainState_EntranceAndLuggage = 1;
int brainState_EntranceAndNoLuggage = 2;
int brainState_WaitingAndLuggage = 3;
int brainState_WaitingAndNoLuggage = 4;

// ---------------------------------------------- Distance sensors utility functions

void setupUserRec() {
  pinMode(userPin_Entrance, INPUT);
  pinMode(userPin_Waiting, INPUT);
  pinMode(luggagePin, INPUT);
}

void getUseronEntrance() {
  if(1 == digitalRead(userPin_Entrance)) {
    entrance_State = true;
    waiting_State = false;
  }
}

void getUseronWaiting() {
  if(1 == digitalRead(userPin_Waiting)) {
    waiting_State = true;
    entrance_State = false;
  }
}

void getIfLuagge() {
  if(1 == digitalRead(luggagePin)) {
    luggage_State = true;
  } else {
    luggage_State = false;
  }
}

void setBrainState() {
  // user at entrance
  if (entrance_State) {
    // if luggage there
    if(luggage_State) {
      current_brainState = brainState_EntranceAndLuggage;
    } else {
      current_brainState = brainState_EntranceAndNoLuggage;
    }
  } else if (waiting_State) {
    if(luggage_State) {
      current_brainState = brainState_WaitingAndLuggage;
    } else {
      current_brainState = brainState_WaitingAndNoLuggage;
    }
  } else {
    current_brainState = brainState_idle;
  }
}
