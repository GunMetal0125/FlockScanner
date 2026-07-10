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
void triggerAlert() {
    Serial.println("ALERT: FLOCK CAMERA NEARBY!");

    // Example buzzer
    tone(GPIO_NUM_15, 2000, 200);

    // Example LED
    digitalWrite(LED_PIN, HIGH);
}
