#include "Task.h"
class DirectMorseTask : public Task {
private:
    bool lastState;
    unsigned long lastUpdate;
public:
    DirectMorseTask();

    void update() override ;

};