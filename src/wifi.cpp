#include "wifi.h"
#include <WiFi.h>
#include <vector>

// ---------------------------
//  FLOCK MAC PREFIX CHECK
// ---------------------------
bool isFlockMAC(const String &mac) {
    String m = mac;
    m.toUpperCase();

    if (m.startsWith("8C:1F:64")) return true;
    if (m.startsWith("AC:8A"))    return true;
    if (m.startsWith("F4:12:FA")) return true;

    return false;
}

// ---------------------------
//  HIT TRACKING
// ---------------------------
struct Hit {
    unsigned long time;
    String mac;
};

std::vector<Hit> hits;

void recordMAC(const String &mac) {
    hits.push_back({millis(), mac});
}

int countRecentHits(unsigned long windowMs) {
    unsigned long now = millis();
    int count = 0;

    for (auto &h : hits) {
        if (now - h.time <= windowMs) count++;
    }

    return count;
}

// ---------------------------
//  ALERT
// ---------------------------
#define BUZZER_PIN 15
#define LED_PIN 2

void triggerAlert() {
    Serial.println("ALERT: FLOCK CAMERA NEARBY!");
    tone(BUZZER_PIN, 2000, 200);
    digitalWrite(LED_PIN, HIGH);
}

// ---------------------------
//  INIT
// ---------------------------
void initWiFiScanner() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

// ---------------------------
//  MAIN SCAN LOOP
// ---------------------------
void scanForFlock() {
    int n = WiFi.scanNetworks();

    for (int i = 0; i < n; i++) {
        String mac = WiFi.BSSIDstr(i);

        if (isFlockMAC(mac)) {
            Serial.println("FLOCK CAMERA DETECTED: " + mac);
            recordMAC(mac);

            if (countRecentHits(5000) >= 3) {
                triggerAlert();
            }
        }
    }
}
