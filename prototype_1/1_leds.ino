// LEDs
// port D7 on Seeeduino Lotus

#include <Adafruit_NeoPixel.h>
#define PIN            8
#define NUMPIXELS      64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

boolean ledsOn = false;

int led_status = 0;

const int led_status_idle = 0;
const int led_status_highlighted = 1;
const int led_status_attracted = 2;
const int led_status_inUse = 3;




// ---------------------------------------------- Leds utility functions

void setupLeds() {
  pixels.begin();
}


// ---------------------------------------------- Leds effect functions

void setMatrixColor(int r, int g, int b) {
  if (ledsOn) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
  } else {
    setMatrixColor(0, 0, 0);
  }
  pixels.show();
}

void setLedsOn(boolean setledsOn) {
  ledsOn = setledsOn;  
}

void setLedStatus() {
  Serial.println(distance);
  switch(distance) {
    case -1 : 
      led_status = led_status_idle;
      Serial.println("gone");
    break;
    default :
      if(50>=distance) {
        Serial.println("near");
      } else if (200 >= distance) {
        Serial.println("far");
      } 
    break;
  }
}


// ---------------------------------------------- Acting Machine control flow
