#include <Arduino.h>
#include "LGFX_ILI9486.hpp"

static LGFX tft;

void initDisplay() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}