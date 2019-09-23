#include <Adafruit_NeoPixel.h>
#define PIN            8
#define NUMPIXELS      64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

boolean ledsOn = false;


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
