#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#include "DefinitionsAndSettings.h"
#include "CommandDecoder.h"


void setup() {
  SPI.begin(SPI_SCK_Pin, SPI_MISO_Pin, SPI_MOSI_Pin, SPI_SS_Pin);
  
  Serial.begin(9600); // Start the serial communication
  Serial.println("Start");

commandDecoderSetup();
  LoRa.setPins(SPI_SS_Pin, SPI_RST_Pin, SPI_DI0_Pin);

  // Initialize LoRa library
  if (!LoRa.begin(915E6)) { 
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  LoRa.setSyncWord(0x34);
 
}

int counter = 0;
void loop(){
  LoRa.beginPacket();
  LoRa.print("Hello, LoRa!");
  LoRa.print(counter);
  LoRa.endPacket();
  delay(1000);
  counter++;
  Serial.println(counter);
  checkSerialCommands();
}
