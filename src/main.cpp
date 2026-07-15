#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <SD.h>
#include "LGFX_ILI9486.hpp"

// =========================
//  Display
// =========================
LGFX_ILI9486 tft;

// =========================
//  WiFi Scanner Settings
// =========================
const char* TARGET_MAC = "F4:12:FA";   // Flock prefix
unsigned long lastScan = 0;
bool flockDetected = false;

// =========================
//  LED Pin
// =========================
#define LED_PIN 4

// =========================
//  Setup
// =========================
void setup() {
  Serial.begin(115200);
  delay(200);

  // LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Display Init
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  // SD Card Init
  if (!SD.begin()) {
    Serial.println("SD FAILED!");
    tft.fillScreen(BLACK);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.setCursor(10, 10);
    tft.println("SD CARD ERROR");
    delay(2000);
  } else {
    // Boot Logo
    if (SD.exists("/badalien.jpg")) {
      tft.drawJpgFile(SD, "/badalien.jpg", 0, 0);
    } else {
      tft.fillScreen(BLACK);
      tft.setTextColor(GREEN);
      tft.setTextSize(4);
      tft.setCursor(20, 20);
      tft.println("BAD ALIEN");
    }
    delay(2000);
  }

  tft.fillScreen(BLACK);

  // WiFi Scanner Init
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Flock Detector Ready");
}

// =========================
//  Loop
// =========================
void loop() {
  unsigned long now = millis();

  // Scan every 2 seconds
  if (now - lastScan > 2000) {
    lastScan = now;

    int n = WiFi.scanNetworks(false, true);
    flockDetected = false;

    for (int i = 0; i < n; i++) {
      String mac = WiFi.BSSIDstr(i);
      if (mac.startsWith(TARGET_MAC)) {
        flockDetected = true;
        break;
      }
    }

    // Update Display + LED
    tft.fillScreen(BLACK);
    tft.setCursor(10, 10);

    if (flockDetected) {
      tft.setTextColor(GREEN);
      tft.setTextSize(3);
      tft.println("FLOCK CAMERA FOUND!");
      digitalWrite(LED_PIN, HIGH);
    } else {
      tft.setTextColor(RED);
      tft.setTextSize(3);
      tft.println("NO FLOCK NEARBY");
      digitalWrite(LED_PIN, LOW);
    }
  }
}
