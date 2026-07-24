#pragma once

#include <Arduino.h>

// Function declarations
void processWifiScan();
void updateDisplayUI(bool target, String mac, int rssi, int channel);
void logDetection(String mac, int rssi);

// Shared variable declarations
extern bool targetDetected;
extern String lastMAC;
extern int lastRSSI;
extern int currentChannel;
