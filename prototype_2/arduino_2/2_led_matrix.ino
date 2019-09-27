// LEDs
// port D7 on Seeeduino Lotus

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(64, 6, NEO_GRBW + NEO_KHZ800);


// ---------------------------------------------- Leds utility functions


void setupMatrix() {
  pixels.begin();
}


// ---------------------------------------------- Leds effect functions



// currently disabled due to single LED use
void setMatrixColor(int r, int g, int b) {
  if (1) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
   }
  } else {
    setMatrixColor(0, 0, 0);
  }
  pixels.show();
}
