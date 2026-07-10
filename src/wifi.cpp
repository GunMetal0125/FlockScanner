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
