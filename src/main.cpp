void loop() {
    ScanResult result = scanForFlock();

    display.clearDisplay();
    display.setCursor(0, 0);

    display.println("Scanning...");
    display.print("Network: ");
    display.println(result.networkCount);

    // Show SSID names
    display.println(result.detectedMAC);

    display.display();
    delay(2000);
}
