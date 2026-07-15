#include "storage.h"
#include <FS.h>
#include <SD.h>

void initStorage() {
    SD.begin(5);
}

void logData(GPSData d) {
    File file = SD.open("/gpslog.txt", FILE_APPEND);
    if (file) {
        file.printf("%f,%f\n", d.lat, d.lng);
        file.close();
    }
}