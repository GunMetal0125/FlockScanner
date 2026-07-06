#pragma once

struct GPSData {
    double lat;
    double lng;
    bool valid;
};

void initGPS();
GPSData readGPS();
