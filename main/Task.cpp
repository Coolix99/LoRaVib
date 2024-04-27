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
    BatterySupervisorTask(int analogPin) : pin(analogPin) {
        pinMode(pin, INPUT);
    }

    void update() override {
        int batteryVoltage = analogRead(pin);
        int newStatus = determineBatteryStatus(batteryVoltage);

        if (newStatus != batteryStatus) {
            batteryStatus = newStatus;
            if (batteryStatus != lastBatteryStatus) {
                lastBatteryStatus = batteryStatus;
                // Status has changed, create a message task
                mainTaskManager.addTask(new MessageTask("..."));
            }
        }
    }

private:
    int determineBatteryStatus(int voltage) {
        if (voltage < 512) return 2; // Example thresholds
        if (voltage < 768) return 1;
        return 0;
    }
};

class MessageTask : public Task {
private:
    String message;
    bool complete = false;

public:
    MessageTask(String msg) : message(msg) {}

    void update() override {
        Serial.println(message);
        isComplete = true; // Mark as complete after showing the message
    }

};