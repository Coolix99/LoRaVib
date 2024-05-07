#include "Task.h"
class DirectMorseReciveTask : public Task {
private:
    bool lastState;
    unsigned long lastUpdate;
public:
    DirectMorseReciveTask();
    void update() override ;
  
    bool targetPegel;
};