#ifndef STORAGE_H
#define STORAGE_H

struct GPSData {
    // We defined both short and long names so nothing breaks!
    float lat;
    float latitude;
    
    float lng;
    float longitude;
    
    float altitude;
};

void initStorage();
void logData(GPSData d);

#endif // STORAGE_H
