#pragma once
#include <Arduino.h>
#include "gps.h"

void initDisplay();
void displayMessage(String msg);
void displayGPS(GPSData d);
