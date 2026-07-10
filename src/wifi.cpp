void setup() {
  Serial.begin(115200);

  initLED();
  initDisplay();
  initGPS();
  initStorage();
  initWiFiScanner();   // <-- CORRECT

  displayMessage("Flock Detector Ready");
}
int n = WiFi.scanNetworks();

for (int i = 0; i < n; i++) {
    String mac = WiFi.BSSIDstr(i);

    if (isFlockMAC(mac)) {
        Serial.println("FLOCK CAMERA DETECTED: " + mac);

        recordMAC(mac);  // your rolling hit counter

        if (countRecentHits(5000) >= 3) {
            triggerAlert();  // buzzer, LED, display, etc.
        }
    }
}
String macToString(const uint8_t *mac) {
    char buf[18];
    sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}
struct Hit {
    unsigned long time;
    String mac;
};

std::vector<Hit> hits;

void recordMAC(const String &mac) {
    hits.push_back({millis(), mac});
}

int countRecentHits(unsigned long windowMs) {
    unsigned long now = millis();
    int count = 0;

    for (auto &h : hits) {
        if (now - h.time <= windowMs) count++;
    }

    return count;
}
void triggerAlert() {
    Serial.println("ALERT: FLOCK CAMERA NEARBY!");

    // Example buzzer
    tone(GPIO_NUM_15, 2000, 200);

    // Example LED
    digitalWrite(LED_PIN, HIGH);
}
#include <WiFi.h>
#include <vector>

// ---------------------------
//  FLOCK MAC PREFIX CHECK
// ---------------------------
bool isFlockMAC(const String &mac) {
    String m = mac;
    m.toUpperCase();

    if (m.startsWith("8C:1F:64")) return true;   // Common Flock ALPR units
    if (m.startsWith("AC:8A"))    return true;   // Newer hardware revisions
    if (m.startsWith("F4:12:FA")) return true;   // 2024–2026 models

    return false;
}

// ---------------------------
//  HIT TRACKING
// ---------------------------
struct Hit {
    unsigned long time;
    String mac;
};

std::vector<Hit> hits;

void recordMAC(const String &mac) {
    hits.push_back({millis(), mac});
}

int countRecentHits(unsigned long windowMs) {
    unsigned long now = millis();
    int count = 0;

    for (auto &h : hits) {
        if (now - h.time <= windowMs) count++;
    }

    return count;
}

// ---------------------------
//  ALERT
// ---------------------------
#define BUZZER_PIN 15
#define LED_PIN 2

void triggerAlert() {
    Serial.println("ALERT: FLOCK CAMERA NEARBY!");

    tone(BUZZER_PIN, 2000, 200);
    digitalWrite(LED_PIN, HIGH);
}

// ---------------------------
//  MAIN SCAN LOOP
// ---------------------------
void scanForFlock() {
    int n = WiFi.scanNetworks();

    for (int i = 0; i < n; i++) {
        String mac = WiFi.BSSIDstr(i);

        if (isFlockMAC(mac)) {
            Serial.println("FLOCK CAMERA DETECTED: " + mac);

            recordMAC(mac);

            if (countRecentHits(5000) >= 3) {
                triggerAlert();
            }
        }
    }
}

// ---------------------------
//  SETUP
// ---------------------------
void setup() {
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();  // required for scanning
    delay(100);
}

// ---------------------------
//  LOOP
// ---------------------------
void loop() {
    scanForFlock();
    delay(1500);  // scan every 1.5 seconds
}
