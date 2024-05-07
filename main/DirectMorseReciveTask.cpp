#include "DirectMorseReciveTask.h"
#include <LoRa.h>
#include "DefinitionsAndSettings.h"

DirectMorseReciveTask::DirectMorseReciveTask(){
  lastUpdate=millis();
  lastState=0;
  targetPegel=0;
}

void DirectMorseReciveTask::update(){
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