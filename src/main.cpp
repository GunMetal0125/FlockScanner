#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C address for SSD1306
#define OLED_ADDR 0x3C

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin(21, 22);  // SDA=21, SCL=22

  // Initialize serial
  Serial.begin(115200);
  delay(1000);

  Serial.println("Initializing OLED...");

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED FAILED TO START");
    while (true);
  }

  Serial.println("OLED started!");

  // Clear screen
  display.clearDisplay();

  // Set text
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("HELLO A!");
  display.setTextSize(1);
  display.println("Your OLED works!");
  display.display();
}

void loop() {
  // Nothing needed here
}
