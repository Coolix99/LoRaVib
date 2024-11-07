#include "TouchButton.h"
#include <Arduino.h>

#define THRESHOLD1 15000
#define THRESHOLD2 500000

#define morseThreshhold_press 200
#define morseThersshold_pause 500

TouchButton::TouchButton(int p)
  : pin(p), lastState(0), currentState(0), rising(0), falling(0), lastChangeTime(0), morseDecoderPressDetected(0) {
}

void TouchButton::update() {
  int value = touchRead(pin);
  if (value < THRESHOLD1) {
    //morseCodeAssembler
    if (morseDecoderPressDetected) {
      morseDecoderPressDetected = false;
      Serial.print("release deteccted ");
      Serial.println(millis() - lastChangeTime);
      if (millis() - lastChangeTime < morseThreshhold_press) {
        rawMorseBuffer += ".";
      } else {
        rawMorseBuffer += "_";
      }
      Serial.println(rawMorseBuffer);
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
    morseDecoderPressDetected = true;
  } else {
    currentState = 2;
    lastChangeTime = millis();
    morseDecoderPressDetected = true;
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

String TouchButton::popBuffer() {
  return "";
}

// Function to convert Morse code to a letter
String TouchButton::morseCodeLUT(String morse) {
     if (morse == ".-") return "A";
    else if (morse == "-...") return "B";
    else if (morse == "-.-.") return "C";
    else if (morse == "-..") return "D";
    else if (morse == ".") return "E";
    else if (morse == "..-.") return "F";
    else if (morse == "--.") return "G";
    else if (morse == "....") return "H";
    else if (morse == "..") return "I";
    else if (morse == ".---") return "J";
    else if (morse == "-.-") return "K";
    else if (morse == ".-..") return "L";
    else if (morse == "--") return "M";
    else if (morse == "-.") return "N";
    else if (morse == "---") return "O";
    else if (morse == ".--.") return "P";
    else if (morse == "--.-") return "Q";
    else if (morse == ".-.") return "R";
    else if (morse == "...") return "S";
    else if (morse == "-") return "T";
    else if (morse == "..-") return "U";
    else if (morse == "...-") return "V";
    else if (morse == ".--") return "W";
    else if (morse == "-..-") return "X";
    else if (morse == "-.--") return "Y";
    else if (morse == "--..") return "Z";
    else if (morse == ".-.-.") return "\n"; //used to end/execute a command
    else return "?"; // Return "?" for unknown Morse code
}
