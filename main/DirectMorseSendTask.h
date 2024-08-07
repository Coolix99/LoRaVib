#include "Task.h"
#include "TouchButton.h"
class DirectMorseSendTask : public Task {
private:
    bool lastState;
    TouchButton* sendTouchButton;
    unsigned long lastUpdate;
public:
    DirectMorseSendTask(TouchButton* tb);

    void update() override ;

};