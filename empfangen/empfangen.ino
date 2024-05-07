#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#include "DefinitionsAndSettings.h"



void setup() {
  SPI.begin(SPI_SCK_Pin, SPI_MISO_Pin, SPI_MOSI_Pin, SPI_SS_Pin);
  
  Serial.begin(9600); // Start the serial communication

  LoRa.setPins(SPI_SS_Pin, SPI_RST_Pin, SPI_DI0_Pin);

  // Initialize LoRa library
  if (!LoRa.begin(915E6)) { 
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  LoRa.setSyncWord(0x34);
 
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
    Serial.print("Received packet '");

    // Read packet
    while (LoRa.available()) {
      String received = LoRa.readString();
      Serial.print(received);
    }

    // Print RSSI of the packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
