class TouchButton : public Task  {
private:
    int pin
    int lastState;
    int currentState;
    int rising;
    int falling;

public:
    TouchButton(int p);
    void update() override ;
  
    int getState();
    bool getTouched();
    bool getPressed();
    int getRising();
    bool getRisingTouched();
    bool getRisingPressed();
    int getFalling();
    bool getFallingTouched();
    bool getFallingPressed();
    
};