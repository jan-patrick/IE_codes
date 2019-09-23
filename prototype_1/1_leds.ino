// LEDs
// port D7 on Seeeduino Lotus

//#include <Adafruit_NeoPixel.h>
//#define PIN            8
//#define NUMPIXELS      64
#include <FastLED.h>

const int lam_num_leds = 1;
CRGB leds[lam_num_leds];


// Collection of states for Led Animation Machine (lam)
const int lam_state_off = 0;
const int lam_state_on = 1;
const int lam_state_blink = 2;
const int lam_state_fade = 3;
const int lam_state_rainbow = 4;

// Remember the current state
int lam_current_state = lam_state_off;

// Make it possible to track the passing of time
long lam_timer_duration = 1000;
long lam_timer_mark = 0;

// Variable to control blinking
int lam_blink_state = 0;
int lam_blink_update_tempo = 1000;

// Variables to control fading
long lam_fade_duration = 2000;
int lam_fade_steps = 40;
int lam_fade_update_tempo = lam_fade_duration / lam_fade_steps;
int lam_fade_direction = 1;
int lam_fade_max = 255;
int lam_fade_min = 0;
int lam_fade_brightness_increment = (lam_fade_max - lam_fade_min) / lam_fade_steps;
int lam_fade_brightness = 0;

// Variable to control the color rainbow
long lam_rainbow_update_tempo = 50;
int lam_rainbow_hue_step = 10;

// Variable to control led color [0..255]
// red=0 orange=32 yellow=64 green=96 blue=160 purple=192 pink=224
int lam_led_hue = 96;

//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

boolean ledsOn = false;

int led_status = 0;

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
    Serial.println("on");
  FastLED.show();
}

void ledOff() {
  for (int i = 0; i < lam_num_leds; i++)
    leds[i].setHSV(lam_led_hue, 255, 0);
  FastLED.show();
  Serial.println("off");
}

void setLedStatus() {
  Serial.println(distance);
  switch (distance) {
    case -1 :
      led_status = led_status_idle;
      ledOff();
      break;
    default :
      if (50 >= distance) {
        ledOn();
      } else if (200 >= distance) {
        ledOn();
      }
      break;
  }
}


// ---------------------------------------------- Acting Machine control flow
