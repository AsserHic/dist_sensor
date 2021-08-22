/*
 Halloween pumpkin
 */

#include <Arduino.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define LED_PIN     12
#define NUM_LEDS    64
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;

void setup() {
  delay(1000); // Initial delay
  FastLED.addLeds<LED_TYPE,
                  LED_PIN,
                  COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}

void loop() {
  FastLED.setBrightness(BRIGHTNESS);
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  EVERY_N_MILLISECONDS(20) { gHue++; }
  
  FastLED.show();
  FastLED.delay(100);
}
