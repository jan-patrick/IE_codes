// Main program file for prototype 1
//
// Uses (check the tabs of your Arduino window):
//   1_distance.ino - for the distance sensor
//   1_leds.ino     - to create led animations
//
// Created September 2019
// By Jan Schneider


const boolean debug = true;

void setup() {
  ///

  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Serial started");
  
  setupDistanceSensor();
  //setupLeds();
}

void loop() {
  //setMatrixColor(200, 100, 100);
  printDistance(getDistance());
}
