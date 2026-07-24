#include <Arduino.h>
#include <WiFi.h>

void initWifiScanner() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void scanWifiNetworks() {
    int n = WiFi.scanNetworks();
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            WiFi.SSID(i);
            WiFi.RSSI(i);
        }
    }
}