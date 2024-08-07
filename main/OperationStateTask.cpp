#include "OperationStateTask.h"
#include "Task.h"
#include "MenuStates.h"


OperationStateTask::OperationStateTask(MenuStates* mS, TouchButton* mTB): mState(mS), menuTouchButton(mTB){
  ;
}

void OperationStateTask::update(){
    String newcommand=menuTouchButton->popBuffer();

    if (newcommand.length() > 1 && newcommand[0] == 'S') {
        char secondChar = newcommand[1];
        switch (secondChar) {
            case 'S':
                mState->output_state = SILENT;
                break;
            case 'V':
                mState->output_state = VIBRATING;
                break;
            case 'F':
                mState->output_state = FULL;
                break;
            default:
                // Handle invalid state if necessary
                break;
        }
    }
}

}