#include <WiFi.h>  // Add this at the top of src/wifi.cpp

void initWifiScanner() {
    WiFi.mode(WIFI_STA);
    // ...
}

void scanWifiNetworks() {
    int n = WiFi.scanNetworks();
    // ...
}
