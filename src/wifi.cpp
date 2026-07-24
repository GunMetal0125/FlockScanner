#include <Arduino.h>
#include <WiFi.h>

void initWifiScanner() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}
