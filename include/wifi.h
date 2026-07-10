#pragma once
#include <Arduino.h>

void initWiFiScanner();
void scanForFlock();

bool isFlockMAC(const String &mac);
void recordMAC(const String &mac);
int countRecentHits(unsigned long windowMs);
void triggerAlert();
