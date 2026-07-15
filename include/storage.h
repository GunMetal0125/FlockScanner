#ifndef STORAGE_H
#define STORAGE_H

struct GPSData {
    float lat;   // We define 'lat' here so d.lat works in storage.cpp
    float lng;   // We define 'lng' here so d.lng works in storage.cpp
    float altitude;
};

void initStorage();
void logData(GPSData d);

#endif // STORAGE_H
