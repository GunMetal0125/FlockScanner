#include <Arduino.h>
#include "wifi_scanner.h"  // <--- ADD THIS LINE AT THE TOP

void setup() {
    // ...
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
