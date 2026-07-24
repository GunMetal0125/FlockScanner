#include <Arduino.h>
#include "LGFX_ILI9486.hpp"

// Initialize global or local display instance
static LGFX tft;

void initDisplay() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}
