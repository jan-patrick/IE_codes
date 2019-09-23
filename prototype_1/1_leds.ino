// LEDs
// port D7 on Seeeduino Lotus

//#include <Adafruit_NeoPixel.h>
//#define PIN            8
//#define NUMPIXELS      64
#include <FastLED.h>

const int lam_num_leds = 1;
CRGB leds[lam_num_leds];


// red=0 orange=32 yellow=64 green=96 blue=160 purple=192 pink=224
int lam_led_hue = 96;
int lam_led_brightness = 0;

//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

unsigned long led_previousMillis = 0;
const long led_normal_interval = 700;

boolean ledsOn = false;
boolean fadeUp = true;

int led_status = 0;
boolean newLedStatusReached = false;

const int led_status_idle = 0;
const int led_status_highlighted = 1;
const int led_status_attracted = 2;
const int led_status_inUse = 3;



// ---------------------------------------------- Leds utility functions


const int clock_pin = 7;
const int data_pin = 8;

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
//    }
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
}

void ledOff() {
  for (int i = 0; i < lam_num_leds; i++)
    leds[i].setHSV(lam_led_hue, 255, 0);
  FastLED.show();
}

void fadeLed() {
  unsigned long led_currentMillis = millis();
  if (led_currentMillis - led_previousMillis >= led_normal_interval) {
    led_previousMillis = led_currentMillis;
    
    if (5 >= lam_led_brightness) {
      adjustLedBrightness(0);
    } else if (40 <= lam_led_brightness && !fadeUp) {
      fadeUp = true;
    } else if (40 <= lam_led_brightness && 60 >= lam_led_brightness) {
      adjustLedBrightness(1);
      Serial.println("e");
    } else if (60 >= lam_led_brightness && fadeUp) {
      fadeUp = false;
    } else if (60 >= lam_led_brightness) {
      adjustLedBrightness(-1);
      Serial.println("üüüe");
    } else {
      adjustLedBrightness(0);
    }
    setLedBrightness();
    Serial.println(lam_led_brightness);
  }
}

void setLedBrightness() {
  for (int i = 0; i < lam_num_leds; i++)
    leds[i].setHSV(lam_led_hue, 255, lam_led_brightness);
  FastLED.show();
}

void adjustLedBrightness(int a) {
  lam_led_brightness += a;
}

void checkLedBrightness() {
  switch (led_status) {
    case led_status_idle :
      if (5 < lam_led_brightness) {
        newLedStatusReached = false;
        adjustLedBrightness(-5);
      } else {
        ledOff();
        lam_led_brightness = 0;
        newLedStatusReached = true;
      }
      break;
    case led_status_highlighted :
      if (50 > lam_led_brightness && !newLedStatusReached) {
        adjustLedBrightness(1);
        newLedStatusReached = false;
      } else if (50 < lam_led_brightness && !newLedStatusReached) {
        adjustLedBrightness(-5);
        newLedStatusReached = false;
      } else {
        newLedStatusReached = true;
      }
      break;
    case led_status_inUse :
      if (250 > lam_led_brightness) {
        adjustLedBrightness(5);
        newLedStatusReached = false;
      } else {
        newLedStatusReached = true;
      }
      break;
    default:
      Serial.println("error");
      break;
  }
  setLedBrightness();
  if (newLedStatusReached) {
    //fadeLed();
  }
}

void setLedStatus() {
  switch (distance) {
    case -1 :
      led_status = led_status_idle;
      break;
    default :
      if (50 >= distance) {
        led_status = led_status_inUse;
      } else if (200 >= distance) {
        led_status = led_status_highlighted;
      }
      break;
  }
}


// ---------------------------------------------- Acting Machine control flow
