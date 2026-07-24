#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <Arduino.h>

// 1. Function Prototypes
void processWifiScan();
void updateDisplayUI(bool target, String mac, int rssi, int channel);
void logDetection(String mac, int rssi);

// 2. Variable Declarations (tells main.cpp these exist elsewhere)
extern bool targetDetected;
extern String lastMAC;
extern int lastRSSI;
extern int currentChannel;

#endif
