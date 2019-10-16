// LEDs
// port D7 on Seeeduino Lotus

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 64

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(64, 6, NEO_GRBW + NEO_KHZ800);

int r = 0;
int g = 0;
int b = 0;

// ---------------------------------------------- Leds utility functions

void setupLedMatrix() {
  pixels.begin();
}


// ---------------------------------------------- Leds effect functions



void setMatrixColor(int ri, int gi, int bi) {
  setMatrixColorR(ri);
  setMatrixColorG(gi);
  setMatrixColorB(bi);
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void setMatrixColorForIndex(int i, int ri, int gi, int bi) {
  setMatrixColorR(ri);
  setMatrixColorG(gi);
  setMatrixColorB(bi);
  pixels.setPixelColor(i, pixels.Color(r, g, b));
  pixels.show();
}

void setMatrixColorinRange(int is, int ie, int ri, int gi, int bi) {
  setMatrixColorR(ri);
  setMatrixColorG(gi);
  setMatrixColorB(bi);
  for (int i = is; i < ie; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
  }
}

void loopMatrixLines() {
  for (int i = 0; i <= 57; i += 8) {
    if (0 < i) {
      setMatrixColorinRange(i - 8, i, 0, 0, 0);
    }
    setMatrixColorinRange(i, i + 8, 255, 255, 255);
    delay(1000);
  }
}

void ledMatrixOn() {
  setMatrixColor(100, 100, 100);
}

void ledMatrixOff() {
  setMatrixColor(0, 0, 0);
}

void setLedMatrixRGB(int ri,  int gi, int bi) {
  setMatrixColorR(ri);
  setMatrixColorG(gi);
  setMatrixColorB(bi);
  setMatrixColor(r, g, b);
}

void setLedMatrixSofa(int ri, int gi, int bi) {
  setMatrixColorR(ri);
  setMatrixColorG(gi);
  setMatrixColorB(bi);
  setMatrixColorForIndex(48, r, g, b);
  setMatrixColorForIndex(49, r, g, b);
  setMatrixColorForIndex(50, r, g, b);
  setMatrixColorForIndex(51, r, g, b);
  setMatrixColorForIndex(52, r, g, b);
  setMatrixColorForIndex(53, r, g, b);
  setMatrixColorForIndex(46, r, g, b);
  setMatrixColorForIndex(45, r, g, b);
  setMatrixColorForIndex(44, r, g, b);
  setMatrixColorForIndex(43, r, g, b);
  setMatrixColorForIndex(42, r, g, b);
  setMatrixColorForIndex(38, r, g, b);
  setMatrixColorForIndex(30, r, g, b);
  setMatrixColorForIndex(22, r, g, b);
  setMatrixColorForIndex(15, r, g, b);
  setMatrixColorForIndex(14, r, g, b);
  setMatrixColorForIndex(7, r, g, b);
}

void setLedMatrixSofaWithoutUser1(int ri, int gi, int bi) {
  setMatrixColorR(ri);
  setMatrixColorG(gi);
  setMatrixColorB(bi);
  setMatrixColorForIndex(48, r, g, b);
  setMatrixColorForIndex(49, r, g, b);
  setMatrixColorForIndex(50, r, g, b);
  setMatrixColorForIndex(52, r, g, b);
  setMatrixColorForIndex(53, r, g, b);
  setMatrixColorForIndex(46, r, g, b);
  setMatrixColorForIndex(45, r, g, b);
  setMatrixColorForIndex(44, r, g, b);
  setMatrixColorForIndex(42, r, g, b);
  setMatrixColorForIndex(38, r, g, b);
  setMatrixColorForIndex(30, r, g, b);
  setMatrixColorForIndex(22, r, g, b);
  setMatrixColorForIndex(15, r, g, b);
  setMatrixColorForIndex(14, r, g, b);
  setMatrixColorForIndex(7, r, g, b);
}

void setMatrixColorR(int ri) {
  r = ri;
  if(255<r) {
    r = 255;
  } else if (0 > r) {
    r = 0;
  }
}
void setMatrixColorG(int gi) {
  g = gi;
  if(255<g) {
    g = 255;
  } else if (0 > g) {
    g = 0;
  }
}

void setMatrixColorB(int bi) {
  b = bi;
  if(255<b) {
    b = 255;
  } else if (0 > b) {
    b = 0;
  }
}
