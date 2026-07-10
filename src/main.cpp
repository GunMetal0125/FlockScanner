#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "wifi.h"

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    Serial.begin(115200);
    delay(800);   // ESP32-WROOM needs a short boot delay

    Wire.begin(); // SDA/SCL auto-select on WROOM-32

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED failed to start");
        while (true);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Flock Detector");
    display.println("OLED OK");
    display.display();

    delay(300);

    initWiFiScanner();
}

void loop() {
    ScanResult result = scanForFlock();

    display.clearDisplay();
    display.setCursor(0, 0);

    if (result.isFlockDetected) {
        display.println("⚠️ FLOCK DETECTED");
        display.println(result.detectedMAC);
        display.print("Hits: ");
        display.println(result.hitCount);
    } else {
        display.println("Scanning...");
        display.print("Networks: ");
        display.println(result.networkCount);
    }

    display.display();
    delay(2000);
}
