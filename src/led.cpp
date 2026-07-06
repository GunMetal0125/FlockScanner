#include "led.h"
#include <Arduino.h>

const int LED_PIN = 2;

void initLED() {
    pinMode(LED_PIN, OUTPUT);
}

void blinkLED() {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
}
