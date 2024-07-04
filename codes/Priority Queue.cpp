#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Task {
    int priority;
    string description;
    
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

int main() {
    priority_queue<Task> taskQueue;
    
    taskQueue.push({2, "Pick items for Order #123"});
    taskQueue.push({1, "Pack items for Order #456"});
    taskQueue.push({3, "Restock shelf A3"});
    
    while (!taskQueue.empty()) {
        Task currentTask = taskQueue.top();
        taskQueue.pop();
        cout << "Executing task: " << currentTask.description << " with priority " << currentTask.priority << endl;
    }
    
    return 0;
}
