#include "wifi.h"
#include <WiFi.h>

static const char* flockPrefixes[] = {
    // Legacy Flock Safety cameras
    "8C:1F:64",
    "AC:8A",
    "F4:12:FA",

    // Newer 2023–2026 vendor blocks
    "D8:3A:DD",
    "E4:5F:01",
    "B4:E6:2D",

    // Additional OEM blocks observed in field deployments
    "40:22:7A",
    "7C:DF:A1"
};

bool isFlockMAC(const String &mac) {
    String m = mac;
    m.toUpperCase();

    for (auto &p : flockPrefixes) {
        if (m.startsWith(p)) return true;
    }

    return false;
}

bool looksLikeFlock(const wifi_ap_record_t &ap) {
    // Flock cameras broadcast a hidden SSID
    if (strlen((char*)ap.ssid) != 0) return false;

    // Channels typically used by Flock Safety hardware
    if (!(ap.primary == 1 || ap.primary == 6 || ap.primary == 11)) return false;

    // Beacon interval signature (Flock uses ~100 TU)
    if (ap.beacon_interval < 90 || ap.beacon_interval > 110) return false;

    // Vendor-specific IE length (Flock uses a unique tag)
    if (ap.ie_len > 0 && ap.ie_len < 50) return true;

    return false;
}

void initWiFiScanner() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void scanForFlock() {
    int n = WiFi.scanNetworks(false, true);

    for (int i = 0; i < n; i++) {
        wifi_ap_record_t ap;
        esp_wifi_sta_get_ap_info(&ap);

        String mac = WiFi.BSSIDstr(i);

        bool macMatch = isFlockMAC(mac);
        bool behaviorMatch = looksLikeFlock(ap);

        if (macMatch || behaviorMatch) {
            Serial.println("⚠️ FLOCK CAMERA DETECTED");
            Serial.println("MAC: " + mac);
            Serial.println("RSSI: " + String(ap.rssi));
            Serial.println("------------------------");

            blinkLED();
        }
    }
}
