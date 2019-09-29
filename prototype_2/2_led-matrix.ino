// LEDs
// port D7 on Seeeduino Lotus

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(64, 8, NEO_GRBW + NEO_KHZ800);



// ---------------------------------------------- Leds utility functions

void setupLedMatrix() {
  pixels.begin();
}


// ---------------------------------------------- Leds effect functions



void setMatrixColor(int r, int g, int b) {
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void setMatrixColorinRange(int is, int ie, int r, int g, int b) {
  pixels.clear();
  for (int i = is; i < ie; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void ledMatrixOn() {
  setMatrixColor(100, 100, 100);
}

void ledMatrixOff() {
  setMatrixColor(0, 0, 0);
}

void setLedMatrixRGB(int r,  int g, int b) {
  setMatrixColor(r, g, b);
}
