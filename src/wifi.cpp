#include <WiFi.h>
#include "wifi_scanner.h"

bool targetDetected = false;
String lastMAC = "";
int lastRSSI = 0;
int currentChannel = 1;

// ... rest of your wifi functions ...
