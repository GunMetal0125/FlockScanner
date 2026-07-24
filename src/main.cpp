#include <Arduino.h>
#include "display.h"
#include "led.h"
#include "wifi.h"
#include "gps.h"
#include "storage.h"

unsigned long alertTimer = 0;
bool lastAlertState = false;

void setup() {
    Serial.begin(115200);

    initLED();
    initDisplay();
    initStorage();
    initGPS();
    initWifiScanner();

    updateDisplayUI(false, lastMAC, lastRSSI, currentChannel);
}

void loop() {
    processWifiScan();
    processGPS();

    if (targetDetected) {
        targetDetected = false;
        alertTimer = millis();
        
        setLEDColor(0, 0, 255); // Turn LED Blue
        logDetection(lastMAC, lastRSSI);
        
        if (!lastAlertState) {
            lastAlertState = true;
            updateDisplayUI(true, lastMAC, lastRSSI, currentChannel);
        }
    }

    // Return to Idle after 5 seconds of no hits
    if (lastAlertState && (millis() - alertTimer >= 5000)) {
        lastAlertState = false;
        setLEDColor(0, 50, 0); // Green
        updateDisplayUI(false, lastMAC, lastRSSI, currentChannel);
    }
}
