#pragma once
#include <Arduino.h>

void initDisplay();
void updateDisplayUI(bool alertActive, const char* macStr, int rssi, int channel);
