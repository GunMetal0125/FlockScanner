#include <WiFi.h>

// ================================================
// Onboard ESP32-S3 RGB LED Pins
// ================================================
#define LED_R 47
#define LED_G 48
#define LED_B 45

// WiFi detection flag
bool wifiNetworksFound = false;

// ================================================
// LED Helper Functions
// ================================================
void blinkBlue() {
    digitalWrite(LED_B, HIGH);
    delay(150);
    digitalWrite(LED_B, LOW);
    delay(150);
}

void blinkRed() {
    digitalWrite(LED_R, HIGH);
    delay(150);
    digitalWrite(LED_R, LOW);
    delay(150);
}

void gpsGreen() {
    digitalWrite(LED_G, HIGH);   // stays on
}

// ================================================
// Setup
// ================================================
void setup() {
    // LED setup
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);

    // WiFi setup
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(1000);
}

// ================================================
// Loop
// ================================================
void loop() {

    // -----------------------------------------------
    // WIFI SCAN
    // -----------------------------------------------
    int n = WiFi.scanNetworks();

    if (n > 0) {
        wifiNetworksFound = true;
    } else {
        wifiNetworksFound = false;
    }

    // -----------------------------------------------
    // WIFI NETWORKS DETECTED -> RED BLINK
    // -----------------------------------------------
    if (wifiNetworksFound) {
        blinkRed();    // blink red
    }

    // -----------------------------------------------
    // FLOCK CAMERA DETECTED -> BLUE BLINK (placeholder)
    // -----------------------------------------------
    // When you add flock detection later:
    // if (isFlockDetected) blinkBlue();

    delay(500);
}
WiFi.mode(WIFI_STA);
WiFi.disconnect();
delay(100);

int n = WiFi.scanNetworks(false, true);

Serial.println("Networks found: " + String(n));

if (n > 0) {
    wifiNetworksFound = true;
} else {
    wifiNetworksFound = false;
}
