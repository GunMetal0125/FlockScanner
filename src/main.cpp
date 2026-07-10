#include <Arduino.h>
#include "wifi.h"

void setup() {
    Serial.begin(115200);
    delay(500);

    // Initialize WiFi scanning system
    initWiFiScanner();

    Serial.println("Flock Detector started");
}

void loop() {
    // Run Flock detection scan
    scanForFlock();

    // Small delay between scans
    delay(2000);
}
