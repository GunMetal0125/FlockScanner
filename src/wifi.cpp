#include "wifi.h"
#include <WiFi.h>
#include "esp_wifi.h"

volatile bool targetDetected = false;
char lastMAC[18] = "00:00:00:00:00:00";
int lastRSSI = 0;
uint8_t currentChannel = 1;

static unsigned long lastHop = 0;

const uint8_t TARGET_OUIS[][3] = {
    {0xD4, 0xAD, 0xFC}, {0xAC, 0x67, 0xB2}, {0x84, 0xF3, 0xEB},
    {0xB4, 0xE6, 0x2D}, {0xCC, 0xDB, 0xA7}, {0x24, 0x0A, 0xC4}
};

typedef struct {
    uint16_t frame_control;
    uint16_t duration;
    uint8_t  addr1[6];
    uint8_t  addr2[6];
    uint8_t  addr3[6];
    uint16_t seq_ctrl;
} __attribute__((packed)) wifi_mgmt_header_t;

void promiscuousCB(void* buf, wifi_promiscuous_pkt_type_t type) {
    if (type != WIFI_PKT_MGMT) return;

    const wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
    const wifi_mgmt_header_t* header = (wifi_mgmt_header_t*)pkt->payload;

    if (((header->frame_control >> 4) & 0x0F) == 4) { // Probe Request
        for (auto& oui : TARGET_OUIS) {
            if (header->addr2[0] == oui[0] &&
                header->addr2[1] == oui[1] &&
                header->addr2[2] == oui[2]) {
                
                targetDetected = true;
                lastRSSI = pkt->rx_ctrl.rssi;
                snprintf(lastMAC, sizeof(lastMAC), "%02X:%02X:%02X:%02X:%02X:%02X",
                         header->addr2[0], header->addr2[1], header->addr2[2],
                         header->addr2[3], header->addr2[4], header->addr2[5]);
                break;
            }
        }
    }
}

void initWifiScanner() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&promiscuousCB);
}

void processWifiScan() {
    if (millis() - lastHop >= 250) {
        lastHop = millis();
        currentChannel = (currentChannel % 11) + 1;
        esp_wifi_set_channel(currentChannel, WIFI_SECOND_CHAN_NONE);
    }
}
