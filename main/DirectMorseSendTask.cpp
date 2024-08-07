#include "DirectMorseSendTask.h"
#include <LoRa.h>
#include "DefinitionsAndSettings.h"


DirectMorseSendTask::DirectMorseSendTask(TouchButton* tb): sendTouchButton(tb){
  lastState=0;
  lastUpdate=millis();
}

void DirectMorseSendTask::update(){
  bool currentState=sendTouchButton->getTouched();
  unsigned long currentTime=millis();
  if ((currentState==lastState) && (currentTime-lastUpdate<1000))
    return;
  LoRa.beginPacket();
  LoRa.print(currentState);
  LoRa.endPacket();
  LoRa.receive();
  Serial.println("send: "+String(currentState));
  lastState=currentState;
  lastUpdate=currentTime;
}