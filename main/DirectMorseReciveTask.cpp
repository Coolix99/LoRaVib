#include "DirectMorseReciveTask.h"
#include <LoRa.h>
#include "DefinitionsAndSettings.h"

DirectMorseReciveTask::DirectMorseReciveTask(){
  lastUpdate=millis();
  lastState=0;
  targetPegel=0;
}

void DirectMorseReciveTask::update(){
  unsigned long currentTime=millis();
  if (lastState!=targetPegel){
    digitalWrite(testLED,targetPegel);
    lastState=targetPegel;
    lastUpdate=currentTime;
    return;
  }
  
  if (currentTime-lastUpdate>1500)
    digitalWrite(testLED,0);
    lastUpdate=currentTime;
}