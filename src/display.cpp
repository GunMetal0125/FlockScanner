#include <Arduino.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// Configuration for your 3.5-inch ILI9486 directly in this file
class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ILI9486 _panel_instance;
    lgfx::Bus_SPI       _bus_instance;

public:
    LGFX() {
        {
            auto cfg = _bus_instance.config();
            cfg.spi_host = SPI2_HOST;
            cfg.spi_mode = 0;
            cfg.freq_write = 40000000;
            cfg.pin_sclk = 12; // Adjust these to match your board's wiring
            cfg.pin_mosi = 11;
            cfg.pin_miso = 13;
            cfg.pin_dc   = 10;
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs       = 9;
            cfg.pin_rst      = 14;
            cfg.pin_busy     = -1;
            cfg.panel_width  = 320;
            cfg.panel_height = 480;
            _panel_instance.config(cfg);
        }
        setPanel(&_panel_instance);
    }
};

static LGFX tft;

void initDisplay() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}