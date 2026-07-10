#include <WiFi.h>
#include "wifi.h"

// Rolling buffer
static const int MAX_HITS = 50;
static String hitMACs[MAX_HITS];
static unsigned long hitTimes[MAX_HITS];
static int hitIndex = 0;

// Flock MAC prefixes
static const char* FLOCK_PREFIXES[] = {
    "7C:DF:A1",
    "D8:BC:38",
    "40:22:D8"
};
static const int NUM_PREFIXES = sizeof(FLOCK_PREFIXES) / sizeof(FLOCK_PREFIXES[0]);

void initWiFiScanner() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

bool isFlockMAC(String mac) {
    mac.toUpperCase();
    for (int i = 0; i < NUM_PREFIXES; i++) {
        if (mac.startsWith(FLOCK_PREFIXES[i])) {
            return true;
        }
    }
    return false;
}

void recordMAC(String mac) {
    hitMACs[hitIndex] = mac;
    hitTimes[hitIndex] = millis();
    hitIndex = (hitIndex + 1) % MAX_HITS;
}

int countRecentHits(unsigned long window) {
    unsigned long now = millis();
    int count = 0;

    for (int i = 0; i < MAX_HITS; i++) {
        if (hitMACs[i].length() == 0) continue;
        if (now - hitTimes[i] <= window) {
            count++;
        }
    }
    return count;
}

void triggerAlert() {
    Serial.println("⚠️  FLOCK CAMERA DETECTED!");
}

ScanResult scanForFlock() {
    ScanResult result;
    result.isFlockDetected = false;
    result.detectedMAC = "";
    result.hitCount = 0;

    int n = WiFi.scanNetworks(false, true);

    for (int i = 0; i < n; i++) {
        String mac = WiFi.BSSIDstr(i);

        if (isFlockMAC(mac)) {
            recordMAC(mac);

            int hits = countRecentHits(30000);

            if (hits >= 3) {
                triggerAlert();
            }

            result.isFlockDetected = true;
            result.detectedMAC = mac;
            result.hitCount = hits;
        }
    }

    WiFi.scanDelete();
    return result;
}