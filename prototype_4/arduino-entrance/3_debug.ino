

// ---------------------------------------------- debug utility functions

void setupDebugging() {
  Serial.begin(9600);

  // wait until serial port opens for native USB devices
  //while (! Serial) {
  //  delay(1);
  //}

  //Serial.println("Serial started");
}

void printSerial_int(String namevar, int var) {
  Serial.println(namevar + ": " + var);
}
