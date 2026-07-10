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
    delay(500);

    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED failed to start");
        while (true);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Flock Detector");
    display.println("WiFi Scanner Ready");
    display.display();

    // Initialize WiFi scanning
    initWiFiScanner();
}

void loop() {
    scanForFlock();

    // OLED heartbeat
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Scanning...");
    display.display();

    delay(2000);
}
