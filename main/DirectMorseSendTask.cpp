#include "directMorseSendTask.h"
#include <LoRa.h>
#include "DefinitionsAndSettings.h"

DirectMorseSendTask::DirectMorseSendTask(){
  lastUpdate=millis();
  lastState=0;
}

void DirectMorseSendTask::update(){
  bool currentState=digitalRead(testButton);
  unsigned long currentTime=millis();
  if ((currentState==lastState) && (currentTime-lastUpdate<1000))
    return;
  LoRa.beginPacket();
  LoRa.print(currentState);
  LoRa.endPacket();
  LoRa.receive();
  Serial.println(currentState);
  lastState=currentState;
  lastUpdate=currentTime;
}