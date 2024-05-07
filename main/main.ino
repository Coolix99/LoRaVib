#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#include "CommandDecoder.h"
#include "TaskManager.h"
//#include "SerialPrintTask.h"
#include "directMorseTask.h"
#include "DefinitionsAndSettings.h"

TaskManager mainTaskManager;

void onReceive(int packetSize) {
  if (packetSize) {
    // Read incoming message
    String incoming = "Message received: ";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
     Serial.println(incoming);
    
  }
}

void setup() {
  SPI.begin(SPI_SCK_Pin, SPI_MISO_Pin, SPI_MOSI_Pin, SPI_SS_Pin);
  
  Serial.begin(9600); // Start the serial communication

  commandDecoderSetup();

  LoRa.setPins(SPI_SS_Pin, SPI_RST_Pin, SPI_DI0_Pin);

  // Initialize LoRa library
  if (!LoRa.begin(915E6)) { 
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  LoRa.setSyncWord(0x34);
  LoRa.onReceive(onReceive);
  
  pinMode(testLED,OUTPUT);

  mainTaskManager.addTask(new DirectMorseTask());

  checkSerialCommands();
  
}


void loop() {
  mainTaskManager.updateTasks();
  delay(100);         
}
