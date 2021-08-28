/*
 Halloween pumpkin
 */

#include <Arduino.h>
#include <FastLED.h>
#include <Adafruit_TiCoServo.h>

FASTLED_USING_NAMESPACE

#define SERVO_PIN 9

#define CANDLE_PIN 3

#define LED_PIN     12
#define NUM_LEDS    64
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

boolean candleOn = false;

Adafruit_TiCoServo tongue;

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;
float phase = 0.0;

void setup() {
  pinMode(CANDLE_PIN, OUTPUT);
  digitalWrite(CANDLE_PIN, candleOn);

  tongue.attach(SERVO_PIN);
  tongue.write(0);

  delay(1000); // Initial delay

  FastLED.addLeds<LED_TYPE,
                  LED_PIN,
                  COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  updateEyes();
  updateTongue();
  updateCandle();
}

void updateEyes() {
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  EVERY_N_MILLISECONDS(20) { gHue++; }

  float eye_l = max(0.0, sin(phase));
  float eye_r = max(0.0, sin(phase + PI));
  float eye_c = eye_l + eye_r;
  setEyeBrightness(0, eye_l);
  setEyeBrightness(1, eye_c);
  setEyeBrightness(2, eye_r);
  phase += 0.1;
  if (phase > 20 * PI) {
    phase = 0;
  }

  FastLED.show();
  FastLED.delay(100);
}

void setEyeBrightness(int pos, float scale) {
  unsigned char darkness = 255.0 * scale;
  leds[pos].fadeToBlackBy(darkness);
  leds[pos + 3].fadeToBlackBy(darkness);
}

void updateTongue() {
  if (random(0, 100) < 2) {
    tongue.write(random(30, 160));
  }
}

void updateCandle() {
  if (random(0, 100) < 2) {
    candleOn = !candleOn;
    digitalWrite(CANDLE_PIN, candleOn);
  }
}
