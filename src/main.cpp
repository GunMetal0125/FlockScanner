#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FastLED.h>

// ---------------- OLED CONFIG ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- LED CONFIG ----------------
#define LED_PIN 48        // change if your LED is on another pin
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];

void setup() {
  // Serial
  Serial.begin(115200);
  Serial.println("Booting...");

  // LED init
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  leds[0] = CRGB::Black;
  FastLED.show();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED FAILED TO START!");
    while (true);
  }

  Serial.println("OLED started!");

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Flock");
  display.println("Scanner");
  display.display();
}

void loop() {
  // LED cycle
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(800);

  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(800);

  leds[0] = CRGB::White;
  FastLED.show();
  delay(800);

  leds[0] = CRGB::Black;
  FastLED.show();
  delay(800);
}
