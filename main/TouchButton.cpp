#include "TouchButton.h"
#include <Arduino.h>

#define THRESHOLD1 15000
#define THRESHOLD2 500000

#define morseThreshhold_press 200
#define morseThersshold_pause 500

TouchButton::TouchButton(int p)
  : pin(p), lastState(0), currentState(0), rising(0), falling(0), lastChangeTime(0) {
}

void TouchButton::update() {
  int value = touchRead(pin);
  if (value < THRESHOLD1) {
    //morseCodeAssembler
    Serial.println("release deteccted");
    if (millis() - lastChangeTime < morseThreshhold_press) {
      rawMorseBuffer += ".";
    } else {
      rawMorseBuffer += "_";
    }
    if (millis() - lastChangeTime > morseThersshold_pause) {
      //add morse character to morseMessageBuffer
      Serial.println(rawMorseBuffer);
    }

    currentState = 0;
    lastChangeTime = millis();
  } else if (value < THRESHOLD2) {
    currentState = 1;
    lastChangeTime = millis();
  } else {
    currentState = 2;
    lastChangeTime = millis();
  }

  if (currentState > lastState) {
    rising = currentState;
  } else if (currentState < lastState) {
    falling = lastState;
  } else {
    rising = 0;
  }
  lastState = currentState;
}

int TouchButton::getState() {
  return currentState;
}

bool TouchButton::getTouched() {
  return currentState > 0;
}

bool TouchButton::getPressed() {
  return currentState == 1;
}

int TouchButton::getRising() {
  return rising;
}

bool TouchButton::getRisingTouched() {
  return rising > 0;
}

bool TouchButton::getRisingPressed() {
  return rising == 1;
}

int TouchButton::getFalling() {
  return falling;
}

bool TouchButton::getFallingTouched() {
  return falling > 0;
}

bool TouchButton::getFallingPressed() {
  return falling == 1;
}

String popBuffer() {
  return "";
}