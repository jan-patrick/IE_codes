// LEDs
// port D7 on Seeeduino Lotus

//#include <Adafruit_NeoPixel.h>
//#define NUMPIXELS 64
#include <FastLED.h>

const int lam_num_leds = 1;
CRGB leds[lam_num_leds];


// red=0 orange=32 yellow=64 green=96 blue=160 purple=192 pink=224
int lam_led_hue = 96;
int lam_led_brightness = 0;

//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(64, 8, NEO_GRBW + NEO_KHZ800);

boolean ledsOn = false;

int led_status = 0;

const int led_status_idle = 0;
const int led_status_highlighted = 1;
const int led_status_attracted = 2;
const int led_status_inUse = 3;



// ---------------------------------------------- Leds utility functions


const int clock_pin = 3;
const int data_pin = 4;

void setupLeds() {
  //pixels.begin();
  FastLED.addLeds<P9813, data_pin, clock_pin, RGB>(leds, lam_num_leds);
  ledOff();
}


// ---------------------------------------------- Leds effect functions



// currently disabled due to single LED use
//void setMatrixColor(int r, int g, int b) {
//  if (ledsOn) {
//    for (int i = 0; i < NUMPIXELS; i++) {
//      pixels.setPixelColor(i, pixels.Color(r, g, b));
//   }
//  } else {
//    setMatrixColor(0, 0, 0);
//  }
//  pixels.show();
//}

void setLedsOn(boolean setledsOn) {
  ledsOn = setledsOn;
  if (ledsOn) {
    ledOn();
  } else {
    ledOff();
  }
}

void ledOn() {
  for (int i = 0; i < lam_num_leds; i++)
    leds[i].setHSV(lam_led_hue, 255, 255);
  FastLED.show();
  //setMatrixColor(255, 255, 255);
}

void ledOff() {
  for (int i = 0; i < lam_num_leds; i++)
    leds[i].setHSV(lam_led_hue, 255, 0);
  FastLED.show();
  //setMatrixColor(0, 0, 0);
}

void setLedBrightness() {
  for (int i = 0; i < lam_num_leds; i++)
    leds[i].setHSV(lam_led_hue, 255, lam_led_brightness);
  FastLED.show();
  //setMatrixColor(lam_led_brightness, lam_led_brightness, lam_led_brightness);
}

void adjustLedBrightness(int a) {
  lam_led_brightness += a;
}

void checkLedBrightness() {
  //Serial.println(led_status);
  switch (led_status) {
    case led_status_idle :
      if (5 < lam_led_brightness) {
        adjustLedBrightness(-5);
      } else {
        ledOff();
        lam_led_brightness = 0;
      }
      break;
    case led_status_highlighted :
      if (50 > lam_led_brightness) {
        adjustLedBrightness(1);
      } else if (50 < lam_led_brightness) {
        adjustLedBrightness(-5);
      }
      break;
    case led_status_attracted :
      if (250 > lam_led_brightness) {
        adjustLedBrightness(5);
      }
      break;
    case led_status_inUse :
      if (15 < lam_led_brightness) {
        adjustLedBrightness(-5);
      } else {
        lam_led_brightness = 10;
      }
      break;
    default:
      Serial.println("error");
      break;
  }
  setLedBrightness();
}

void setLedStatus() {
  //Serial.println(lam_led_brightness);
  switch (distance) {
    case -1 :
      led_status = led_status_idle;
      ledOff();
      break;
    default :
      if (50 >= distance) {
        led_status = led_status_inUse;
      } else if (200 >= distance) {
        led_status = led_status_attracted;
      } else if (500 >= distance) {
        led_status = led_status_highlighted;
      }
      break;
  }
}
