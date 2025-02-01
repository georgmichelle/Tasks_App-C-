#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class Task {
public:
    string name;
    string description;
    string deadline;  // Format: YYYY-MM-DD
    bool isCompleted;

    Task(string n, string d, string dl) : name(n), description(d), deadline(dl), isCompleted(false) {}

    void markCompleted() {
        isCompleted = true;
    }

    void displayTask() {
        cout << "Task Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Deadline: " << deadline << endl;
        cout << "Status: " << (isCompleted ? "Completed" : "Pending") << endl;
        cout << "--------------------------" << endl;
    }

    bool isDeadlinePassed() {
        // Check if the task's deadline has passed
        struct tm deadline_tm = {};
        strptime(deadline.c_str(), "%Y-%m-%d", &deadline_tm);
        time_t deadline_time = mktime(&deadline_tm);
        time_t now = time(0);
        return difftime(now, deadline_time) > 0;
    }

    bool compareDeadline(const Task &other) const {
        struct tm this_tm = {}, other_tm = {};
        strptime(deadline.c_str(), "%Y-%m-%d", &this_tm);
        strptime(other.deadline.c_str(), "%Y-%m-%d", &other_tm);
        return mktime(&this_tm) < mktime(&other_tm);
    }
};

class TaskManager {
private:
    vector<Task> tasks;

public:
    void addTask(string name, string description, string deadline) {
        tasks.push_back(Task(name, description, deadline));
    }

    void updateTask(int index, string newName, string newDescription, string newDeadline) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].name = newName;
            tasks[index].description = newDescription;
            tasks[index].deadline = newDeadline;
        }
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        }
    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markCompleted();
        }
    }

    void displayTasks() {
        for (int i = 0; i < tasks.size(); i++) {
            tasks[i].displayTask();
        }
    }

    void displayOverdueTasks() {
        cout << "Overdue Tasks:\n";
        bool hasOverdue = false;
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].isDeadlinePassed() && !tasks[i].isCompleted) {
                tasks[i].displayTask();
                hasOverdue = true;
            }
        }
        if (!hasOverdue) {
            cout << "No overdue tasks.\n";
        }
    }

    void sortTasksByDeadline() {
        sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.compareDeadline(b);
        });
        cout << "Tasks sorted by deadline.\n";
    }

    void displayCompletedTasks() {
        cout << "Completed Tasks:\n";
        bool hasCompleted = false;
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].isCompleted) {
                tasks[i].displayTask();
                hasCompleted = true;
            }
        }
        if (!hasCompleted) {
            cout << "No completed tasks.\n";
        }
    }
};

int main() {
    TaskManager taskManager;

    int choice;
    string name, description, deadline;
    int taskIndex;

    do {
        cout << "Task Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Update Task\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Task as Completed\n";
        cout << "5. Display All Tasks\n";
        cout << "6. Display Overdue Tasks\n";
        cout << "7. Sort Tasks by Deadline\n";
        cout << "8. Display Completed Tasks\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter task name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter task deadline (YYYY-MM-DD): ";
                getline(cin, deadline);
                taskManager.addTask(name, description, deadline);
                break;

            case 2:
                cout << "Enter task index to update: ";
                cin >> taskIndex;
                cout << "Enter new task name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new task description: ";
                getline(cin, description);
                cout << "Enter new task deadline (YYYY-MM-DD): ";
                getline(cin, deadline);
                taskManager.updateTask(taskIndex, name, description, deadline);
                break;

            case 3:
                cout << "Enter task index to delete: ";
                cin >> taskIndex;
                taskManager.deleteTask(taskIndex);
                break;

            case 4:
                cout << "Enter task index to mark as completed: ";
                cin >> taskIndex;
                taskManager.markTaskCompleted(taskIndex);
                break;

            case 5:
                taskManager.displayTasks();
                break;

            case 6:
                taskManager.displayOverdueTasks();
                break;

            case 7:
                taskManager.sortTasksByDeadline();
                break;

            case 8:
                taskManager.displayCompletedTasks();
                break;

            case 9:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 9);

    return 0;
}