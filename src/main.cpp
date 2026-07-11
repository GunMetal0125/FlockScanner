// ===============================
// Onboard ESP32-S3 RGB LED Pins
// ===============================
#define LED_R 47
#define LED_G 48
#define LED_B 45

// ===============================
// LED Helper Functions
// ===============================
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

// ===============================
// Setup
// ===============================
void setup() {
  // LED setup
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  // Your other setup code goes here:
  // Serial.begin(...)
  // WiFi.begin(...)
  // GPS init...
}

// ===============================
// Loop
// ===============================
void loop() {

  // -------------------------------
  // Example: GPS lock detection
  // Replace gps.location.isValid() with your real GPS check
  // -------------------------------
  if (gps.location.isValid()) {
    gpsGreen();   // solid green
  }

  // -------------------------------
  // Example: WiFi networks detected
  // Replace wifiNetworksFound with your real variable
  // -------------------------------
  if (wifiNetworksFound) {
    blinkRed();   // blink red
  }

  // -------------------------------
  // Example: Flock camera detected
  // Replace isFlockDetected with your real detection variable
  // -------------------------------
  if (isFlockDetected) {
    blinkBlue();  // blink blue
  }

  // Your other loop code goes here...
}
