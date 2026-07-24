#include "led.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN 48 // ESP32-S3 onboard RGB LED
Adafruit_NeoPixel rgbLed(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void initLED() {
    rgbLed.begin();
    setLEDColor(0, 50, 0); // Start Green (Idle)
}

void setLEDColor(uint8_t r, uint8_t g, uint8_t b) {
    rgbLed.setPixelColor(0, rgbLed.Color(r, g, b));
    rgbLed.show();
}
