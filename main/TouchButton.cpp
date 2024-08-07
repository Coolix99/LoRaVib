#include "TouchButton.h"
#include <Arduino.h>

#define THRESHOLD1 15000
#define THRESHOLD2 500000

TouchButton::TouchButton(int p) : pin(p), lastState(0), currentState(0), rising(0), falling(0) {
}

void TouchButton::update() {
    int value = touchRead(pin);
    if (value < THRESHOLD1) {
        currentState = 0;
    } else if (value < THRESHOLD2) {
        currentState = 1;
    } else {
        currentState = 2;
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
