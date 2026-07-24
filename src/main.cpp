#include <Arduino.h>
#include "wifi_scanner.h"

void setup() {
    // Initialize hardware (e.g., Serial, Display, Wi-Fi)
    Serial.begin(115200);
}

void loop() {
    processWifiScan();

    if (targetDetected) {
        logDetection(lastMAC, lastRSSI);
        updateDisplayUI(true, lastMAC, lastRSSI, currentChannel);
    } else {
        updateDisplayUI(false, lastMAC, lastRSSI, currentChannel);
    }
}
