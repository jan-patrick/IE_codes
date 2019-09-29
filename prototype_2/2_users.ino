// button for now
// use I2C port

const int buttonPin_Entrance = 4;
const int buttonPin_Waiting = 6;

boolean entrance_State = false;
boolean waiting_State = false;

// ---------------------------------------------- Distance sensors utility functions

void setupUserRec() {
  pinMode(buttonPin_Entrance, INPUT);
}

void getUseronEntrance() {
  if(1 == digitalRead(buttonPin_Entrance)) {
    entrance_State = true;
  } else {
    entrance_State = false;
  }
}

void getUseronWaiting() {
  if(1 == digitalRead(buttonPin_Waiting)) {
    waiting_State = true;
  } else {
    waiting_State = false;
  }
}
