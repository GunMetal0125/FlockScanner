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
