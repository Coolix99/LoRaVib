class TaskManager {
private:
    Task* tasks[10]; // TODO: manage positions better
    int taskCount = 0;

public:
    void addTask(Task* task) {
        if (taskCount < 10) {
            tasks[taskCount++] = task;
        }
    }

    void updateTasks() {
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i]->isComplete) {
                removeTask(i);
                i--; // Adjust the index since we're removing an item
            } else {
                tasks[i]->update();
            }
        }
    }

private:
    void removeTask(int index) {
        if (index < taskCount) {
            for (int j = index; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            taskCount--;
        }
    }
};