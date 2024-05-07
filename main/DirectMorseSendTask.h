#include "Task.h"
class DirectMorseSendTask : public Task {
private:
    bool lastState;
    unsigned long lastUpdate;
public:
    DirectMorseSendTask();

    void update() override ;

};