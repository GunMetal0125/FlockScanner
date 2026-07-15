#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "storage.h" // FIX: Includes the file that defines 'GPSData' so the compiler knows what it is

// This function can now successfully compile because GPSData is defined!
void displayGPS(GPSData d);

#endif // DISPLAY_H
