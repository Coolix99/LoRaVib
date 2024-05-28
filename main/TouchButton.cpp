#include "TouchButton.h"
#include <Arduino.h>

#define THRESHOLD1 15000
#define THRESHOLD2 500000

TouchButton::TouchButton(int p)p:pin{
}

void TouchButton::update(){
    const auto& value=touchRead(pin);
    if value < THRESHOLD1:
      currentState=0;
    else if value < THRESHOLD2
      currentState=1;
    else
      curentState=2;
    
    if currentState > laststate{
      risingState=currentState;
    }
    else if currentState < laststate
      fallingState=lastState;
    else 
      rising=0;
    lastState=currentState;

}

int TouchButton::getState();
bool TouchButton::getTouched();
bool TouchButton::getPressed();
int TouchButton::getRising();
bool TouchButton::getRisingTouched();
bool TouchButton::getRisingPressed();
int TouchButton::getFalling();
bool TouchButton::getFallingTouched();
bool TouchButton::getFallingPressed();