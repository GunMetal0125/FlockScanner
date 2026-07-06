#include "gps.h"
#include <TinyGPSPlus.h>

TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

void initGPS() {
    SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
}

GPSData readGPS() {
    GPSData d;

    while (SerialGPS.available()) {
        gps.encode(SerialGPS.read());
    }

    if (gps.location.isValid()) {
        d.lat = gps.location.lat();
        d.lng = gps.location.lng();
        d.valid = true;
    } else {
        d.valid = false;
    }

    return d;
}
