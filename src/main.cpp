// ================================================
// Onboard ESP32-S3 RGB LED Pins
// ================================================
#define LED_R 47
#define LED_G 48
#define LED_B 45

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
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);

    // Fake startup delay
    delay(1000);
}

// ================================================
// Loop
// ================================================
void loop() {

    // -----------------------------------------------
    // SIMULATED GPS LOCK -> GREEN LED
    // -----------------------------------------------
    gpsGreen();      // solid green
    delay(2000);

    // -----------------------------------------------
    // SIMULATED WIFI NETWORK DETECTED -> RED BLINK
    // -----------------------------------------------
    blinkRed();      // blink red
    delay(1000);

    // -----------------------------------------------
    // SIMULATED FLOCK CAMERA DETECTED -> BLUE BLINK
    // -----------------------------------------------
    blinkBlue();     // blink blue
    delay(1000);
}
