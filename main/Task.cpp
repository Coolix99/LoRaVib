#include <Arduino.h>

class Task {
public:
    virtual void update() = 0; // Method to update task status
    bool isComplete = 0; // status of the task
};

