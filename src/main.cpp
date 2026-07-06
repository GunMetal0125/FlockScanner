#include <Arduino.h>
#include "gps.h"
#include "display.h"
#include "storage.h"
#include "led.h"

void setup() {
    Serial.begin(115200);

    initLED();
    initDisplay();
    initGPS();
    initStorage();

    displayMessage("Flock Detector Ready");
}

void loop() {
    GPSData data = readGPS();

    if (data.valid) {
        logData(data);
        displayGPS(data);
        blinkLED();
    }

    delay(500);
}
