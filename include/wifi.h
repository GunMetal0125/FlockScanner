#pragma once

void initWiFiScanner();
void scanForFlock();

bool isFlockMAC(String mac);
void recordMAC(String mac);
int countRecentHits(unsigned long window);
void triggerAlert();
