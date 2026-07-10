#pragma once
#include <Arduino.h>

struct ScanResult {
    bool isFlockDetected;
    String detectedMAC;
    int hitCount;
};

void initWiFiScanner();
ScanResult scanForFlock();
bool isFlockMAC(String mac);
void recordMAC(String mac);
int countRecentHits(unsigned long window);
void triggerAlert();
