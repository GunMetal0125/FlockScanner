#include <WiFi.h>
#include "wifi_scanner.h"

// Global variables definitions
bool targetDetected = false;
String lastMAC = "";
int lastRSSI = 0;
int currentChannel = 1;

void processWifiScan() {
    // Set Wi-Fi to station mode and disconnect if connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Perform a Wi-Fi network scan
    int n = WiFi.scanNetworks();
    if (n == 0) {
        targetDetected = false;
        return;
    }

    for (int i = 0; i < n; ++i) {
        String mac = WiFi.BSSIDstr(i);
        int rssi = WiFi.RSSI(i);
        int channel = WiFi.channel(i);

        // Update tracking variables
        lastMAC = mac;
        lastRSSI = rssi;
        currentChannel = channel;

        // Add your target identification logic here (e.g., matching a MAC prefix)
        // For testing, flag true if any network is found:
        targetDetected = true; 
    }

    // Clean up scan memory
    WiFi.scanDelete();
}
