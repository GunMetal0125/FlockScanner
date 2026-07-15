#include "display.h"

void displayGPS(GPSData d) {
    // This will now compile perfectly!
    Serial.print("Lat: ");
    Serial.println(d.latitude);
}
