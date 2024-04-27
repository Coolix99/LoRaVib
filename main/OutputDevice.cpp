class OutputDevice {
public:
    virtual void initialize() = 0; // Setup the device
    virtual void show(const String& msg) = 0;   // prints a message
};

class RGBLed : public OutputDevice {
public:
    void initialize() override {
        ; 
    }
    void show(const String& msg) override {
        ; 
    }
};

class VibrationMotor : public OutputDevice {
public:
    void initialize() override {
        ; 
    }
    void show(const String& msg) override {
        ;
    }
 
};