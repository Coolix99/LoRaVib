#include <Arduino.h>

#include "TaskManager.h"
#include "Task.h"

void TaskManager::addTask(Task* task) {
    if (taskCount < 10) {
        tasks[taskCount++] = task;
    }
}

void TaskManager::updateTasks() {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i]->isComplete) {
            removeTask(i);
            i--; // Adjust the index since we're removing an item
        } else {
            tasks[i]->update();
        }
    }
}


void TaskManager::removeTask(int index) {
    if (index > taskCount)
      return;
    delete tasks[index];
    if (taskCount>1)
      tasks[index] = tasks[taskCount-1];
    taskCount--;
}
