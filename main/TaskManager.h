#include "Task.h"

class TaskManager {
private:
    Task* tasks[10]; // TODO: manage positions better
    int taskCount = 0;

public:
    void addTask(Task* task);

    void updateTasks();

private:
    void removeTask(int index);
};