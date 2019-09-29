// LED
// port D3 on Seeeduino Lotus

#include <FastLED.h>

const int lam_num_leds = 1;
CRGB leds[lam_num_leds];

// red=0 orange=32 yellow=64 green=96 blue=160 purple=192 pink=224
int lam_led_hue = 96;
int lam_led_brightness = 0;


// ---------------------------------------------- Leds utility functions


const int clock_pin = 3;
const int data_pin = 4;

void setupLed() {
  FastLED.addLeds<P9813, data_pin, clock_pin, RGB>(leds, lam_num_leds);
}


// ---------------------------------------------- Leds effect functions

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

void setLedBrightness() {
  for (int i = 0; i < lam_num_leds; i++)
    leds[i].setHSV(lam_led_hue, 255, lam_led_brightness);
  FastLED.show();
}

void adjustLedBrightness(int a) {
  lam_led_brightness += a;
}
