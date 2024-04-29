#pragma once
class Task {
public:
    virtual void update() = 0; // Method to update task status
    bool isComplete = 0; // status of the task
};

class BatterySupervisorTask : public Task {
private:
    int pin;
    int batteryStatus = 0; // Example: 0 for normal, 1 for low, 2 for critical
    int lastBatteryStatus = -1; // to track changes in battery status

public:
    BatterySupervisorTask(int analogPin);

    void update() override ;
    

private:
    int determineBatteryStatus(int voltage) ;
};

class MessageTask : public Task {
private:
    String message;
    bool complete = false;

public:
    MessageTask(String msg) : message(msg) {}

    void update() override ;

};