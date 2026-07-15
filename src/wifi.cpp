#include <Arduino.h>
#include <WiFi.h>

// FIX: Added the closing brace and semicolon }; so the compiler doesn't crash
static const char* FLOCK_PREFIXES[] = {
    "F4:12:FA",
    "00:11:22"
}; 

void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}
