#include <Arduino.h>

TaskManager mainTaskManager;

void setup() {
  Serial.begin(9600); // Start the serial communication
  mainTaskManager.addTask(new BatterySupervisorTask(A0)); // A0 is the analog pin used
}

void loop() {
  mainTaskManager.updateTasks();

}
