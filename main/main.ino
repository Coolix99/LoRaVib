#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#include "CommandDecoder.h"
#include "TaskManager.h"

#include "DirectMorseSendTask.h"
#include "DirectMorseReciveTask.h"
#include "TouchButton.h"

#include "DefinitionsAndSettings.h"
#include "MenuStates.h"
#include "OperationStateTask.h"

TaskManager mainTaskManager;
DirectMorseReciveTask mainDirectMorseReciveTask;
TouchButton leftTouchButton(touchButtonLeft_Pin);
TouchButton rightTouchButton(touchButtonRight_Pin);
MenuStates mainMenuStates;


void onReceive(int packetSize) {
  if (packetSize) {
    // Read incoming message
    String incoming = "Message received: ";
    while (LoRa.available()) {
      char loraByte = (char)LoRa.read();
      Serial.println(uint8_t(loraByte));
      incoming += loraByte;
    }
    //Serial.println(incoming);
    mainDirectMorseReciveTask.targetPegel = (incoming.indexOf("1") != -1);
  }
}

void setup() {
  SPI.begin(SPI_SCK_Pin, SPI_MISO_Pin, SPI_MOSI_Pin, SPI_SS_Pin);

  Serial.begin(9600);  // Start the serial communication
  delay(7000);
  commandDecoderSetup();

  pinMode(testLED, OUTPUT);

  LoRa.setPins(SPI_SS_Pin, SPI_RST_Pin, SPI_DI0_Pin);

  // Initialize LoRa library
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1) {
      checkSerialCommands();
    }
  }
  Serial.println("LoRa Initializing OK!");
  LoRa.setSyncWord(0x34);
  LoRa.onReceive(onReceive);

  mainMenuStates.output_state=FULL;
  
  mainTaskManager.addTask(new DirectMorseSendTask(&leftTouchButton));
  mainTaskManager.addTask(&mainDirectMorseReciveTask);
  mainTaskManager.addTask(&leftTouchButton);
  mainTaskManager.addTask(&rightTouchButton);
  mainTaskManager.addTask(new OperationStateTask(&mainMenuStates, &rightTouchButton));

  
}


void loop() {
  mainTaskManager.updateTasks();
  delay(100);
  checkSerialCommands();
}
