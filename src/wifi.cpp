void setup() {
  Serial.begin(115200);

  initLED();
  initDisplay();
  initGPS();
  initStorage();
  initWiFiScanner();   // <-- CORRECT

  displayMessage("Flock Detector Ready");
}
