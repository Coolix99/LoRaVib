#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#include "CommandDecoder.h"
#include "TaskManager.h"
#include "Task.h"
#include "DefinitionsAndSettings.h"



TaskManager mainTaskManager;

void onReceive(int packetSize) {
  if (packetSize) {
    // Read incoming message
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    Serial.print("Message received: ");
    Serial.println(incoming);
  }
}

void setup() {
  SPI.begin(SPI_SCK_Pin, SPI_MISO_Pin, SPI_MOSI_Pin, SPI_SS_Pin);
  
  Serial.begin(9600); // Start the serial communication

  LoRa.setPins(SPI_SS_Pin, SPI_RST_Pin, SPI_DI0_Pin);

  // Initialize LoRa library
  if (!LoRa.begin(915E6)) { // Set frequency to 915 MHz (adjust according to your region)
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  
  LoRa.onReceive(onReceive);
  
}

int counter = 0;
void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  // Start LoRa packet
  LoRa.beginPacket();
  LoRa.print("Hello #"); // Example message
  LoRa.print(counter);  // Incrementing number
  LoRa.endPacket();
  counter++; 
  LoRa.receive();
  delay(3000);         

  //mainTaskManager.updateTasks();

}
