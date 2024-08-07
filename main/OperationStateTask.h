#pragma once

#include "Task.h"
#include "MenuStates.h"
#include "TouchButton.h"

class OperationStateTask : public Task {
private:
    MenuStates* mState;
    TouchButton* menuTouchButton;
public:
    OperationStateTask(MenuStates* mS, TouchButton* mTB);
    void update() override ;

};