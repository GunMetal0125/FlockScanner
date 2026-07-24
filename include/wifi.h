#pragma once
#include <Arduino.h>

extern volatile bool targetDetected;
extern char lastMAC[18];
extern int lastRSSI;
extern uint8_t currentChannel;

void initWifiScanner();
void processWifiScan();
