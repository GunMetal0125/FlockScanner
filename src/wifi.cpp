#include <WiFi.h>
#include "wifi.h"

// Rolling buffer for MAC hits
static const int MAX_HITS = 50;
static String hitMACs[MAX_HITS];
static unsigned long hitTimes[MAX_HITS];
static int hitIndex = 0;

// Put your Flock MAC prefixes here
static const char* FLOCK_PREFIXES[] = {
    "7C:DF:A1",
    "D8:BC:38",
    "40:22:D8"
};
static const int NUM_PREFIXES = sizeof(FLOCK_PREFIXES) / sizeof(FLOCK_PREFIXES[0]);

// ------------------------------------------------------
// Initialize WiFi in STA mode (Arduino compatible)
// ------------------------------------------------------
void initWiFiScanner() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();        // ensures scanning mode
    delay(100);
}

// ------------------------------------------------------
// Check if a MAC matches known Flock prefixes
// ------------------------------------------------------
bool isFlockMAC(String mac) {
    mac.toUpperCase();
    for (int i = 0; i < NUM_PREFIXES; i++) {
        if (mac.startsWith(FLOCK_PREFIXES[i])) {
            return true;
        }
    }
    return false;
}

// ------------------------------------------------------
// Record a MAC hit with timestamp
// ------------------------------------------------------
void recordMAC(String mac) {
    hitMACs[hitIndex] = mac;
    hitTimes[hitIndex] = millis();
    hitIndex = (hitIndex + 1) % MAX_HITS;
}

// ------------------------------------------------------
// Count hits within a time window (ms)
// ------------------------------------------------------
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

// ------------------------------------------------------
// Trigger alert (placeholder)
// ------------------------------------------------------
void triggerAlert() {
    Serial.println("⚠️  FLOCK CAMERA DETECTED!");
}

// ------------------------------------------------------
// Main scan loop — call this repeatedly from main.cpp
// ------------------------------------------------------
void scanForFlock() {
    int n = WiFi.scanNetworks(false, true);  // async=false, show hidden=true

    for (int i = 0; i < n; i++) {
        String mac = WiFi.BSSIDstr(i);

        if (isFlockMAC(mac)) {
            recordMAC(mac);

            int hits = countRecentHits(30000); // 30 seconds window

            if (hits >= 3) {
                triggerAlert();
            }
        }
    }

    WiFi.scanDelete();   // free memory
}
