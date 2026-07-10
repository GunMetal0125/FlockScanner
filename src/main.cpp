#include <FastLED.h>

#define LED_PIN 48
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(100);
}

void loop() {
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(1000);

    leds[0] = CRGB::Green;
    FastLED.show();
    delay(1000);

    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(1000);
}
