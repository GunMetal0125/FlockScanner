#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <SD.h>
#include "LGFX_ILI9486.hpp"
#include "display.h"

// ==========================================
// Display
// ==========================================
LGFX_ILI9486 tft;

// ==========================================
// WiFi Scanner Settings
// ==========================================
const char* TARGET_MAC = "F4:12:FA";  // Flock prefix
unsigned long lastScan = 0;
bool flockDetected = false;

// ==========================================
// LED Pin
// ==========================================
#define LED_PIN 4

// ==========================================
// Setup
// ==========================================
void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    
    // Initialize Display
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.drawString("Scanner Starting...", 10, 10);

    // Set WiFi to Station Mode
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

// ==========================================
// Main Loop
// ==========================================
void loop() {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(10, 10);
    tft.setTextColor(TFT_WHITE);
    tft.print("Scanning WiFi...");

    int n = WiFi.scanNetworks(false, true);
    if (n == 0) {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_RED);
        tft.drawString("No networks found", 10, 50);
    } else {
        tft.fillScreen(TFT_BLACK);
        tft.setTextColor(TFT_GREEN);
        tft.drawString("Networks found!", 10, 50);
    }
    
    delay(5000);
}
