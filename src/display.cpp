#include "display.h"

// Dummy function implementation matching the header declaration
void displayGPS(GPSData d) {
    // Your GPS displaying logic goes here
    Serial.print("Lat: ");
    Serial.println(d.latitude);
}
