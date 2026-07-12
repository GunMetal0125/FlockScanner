#include <SPI.h>
#include <SD.h>

// SPI pin mapping for ESP32-S3
#define SD_CS   5
#define SD_MOSI 11
#define SD_MISO 13
#define SD_CLK  12

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Initializing SD card...");

  // Start SPI bus
  SPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);

  // Mount SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD card mount failed!");
    return;
  }

  Serial.println("SD card mounted successfully!");

  // Write test file
  File file = SD.open("/test.txt", FILE_WRITE);
  if (file) {
    file.println("Hello SD card!");
    file.close();
    Serial.println("Wrote to test.txt");
  } else {
    Serial.println("Failed to open test.txt for writing");
  }

  // Read test file
  file = SD.open("/test.txt");
  if (file) {
    Serial.println("Reading test.txt:");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    Serial.println("Failed to open test.txt for reading");
  }
}

void loop() {
}
