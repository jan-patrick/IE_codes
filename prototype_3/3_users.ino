const long range_luggage = 1000;

const int luggage = A0;

// ---------------------------------------------- Distance sensors utility functions

void setupUserRec() {
  pinMode(A0, INPUT);
}


boolean getIfUser() {
    int sensorValue = analogRead(luggage);
    //Serial.println(sensorValue);
    if (range_luggage <= sensorValue) {
      return true;
    } else {
      return false;
    }
}
