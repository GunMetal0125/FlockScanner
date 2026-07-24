#include "display.h"
#include "LGFX_ILI9486.hpp"

static LGFX_ILI9486 lcd;

void initDisplay() {
    lcd.init();
    lcd.setRotation(1); // Landscape
    lcd.fillScreen(TFT_BLACK);
}

void updateDisplayUI(bool alertActive, const char* macStr, int rssi, int channel) {
    if (alertActive) {
        lcd.fillScreen(TFT_NAVY);
        lcd.fillRect(0, 0, 480, 50, TFT_BLUE);
        lcd.setTextColor(TFT_WHITE, TFT_BLUE);
        lcd.setTextDatum(textdatum_t::middle_center);
        lcd.drawString("!!! FLOCK CAM DETECTED !!!", 240, 25, 4);

        lcd.setTextColor(TFT_CYAN, TFT_NAVY);
        lcd.setTextDatum(textdatum_t::top_left);
        lcd.drawString("Target MAC:", 20, 80, 4);
        lcd.setTextColor(TFT_WHITE, TFT_NAVY);
        lcd.drawString(macStr, 20, 115, 4);

        lcd.setTextColor(TFT_CYAN, TFT_NAVY);
        lcd.drawString("RSSI (Signal):", 20, 160, 4);
        
        char buf[32];
        snprintf(buf, sizeof(buf), "%d dBm", rssi);
        lcd.setTextColor(TFT_YELLOW, TFT_NAVY);
        lcd.drawString(buf, 20, 195, 4);
    } else {
        lcd.fillScreen(TFT_BLACK);
        lcd.fillRect(0, 0, 480, 50, TFT_DARKGREY);
        lcd.setTextColor(TFT_WHITE, TFT_DARKGREY);
        lcd.setTextDatum(textdatum_t::middle_center);
        lcd.drawString("RF SPECTRUM SCANNER", 240, 25, 4);

        lcd.setTextColor(TFT_GREEN, TFT_BLACK);
        lcd.setTextDatum(textdatum_t::top_left);
        lcd.drawString("Status: SCANNING...", 20, 90, 4);

        char chanBuf[32];
        snprintf(chanBuf, sizeof(chanBuf), "Channel: %2d (2.4 GHz)", channel);
        lcd.setTextColor(TFT_WHITE, TFT_BLACK);
        lcd.drawString(chanBuf, 20, 140, 4);
    }
}
