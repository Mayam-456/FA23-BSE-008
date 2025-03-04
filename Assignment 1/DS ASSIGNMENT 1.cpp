#include <iostream>
#include <string>
using namespace std;

// Node structure for a task
struct Task {
    int id;
    string description;
    int priority;
    Task* next;

    // Constructor to initialize task
    Task(int tid, const string& desc, int prio) {
        id = tid;
        description = desc;
        priority = prio;
        next = nullptr;
    }
};

class TaskManager {
private:
    Task* head; // Head of the linked list

public:
    TaskManager() : head(nullptr) {}

    // Function to add a new task based on priority
    void addTask(int id, const string& desc, int priority) {
        Task* newTask = new Task(id, desc, priority);

        if (head == nullptr || priority > head->priority) {
            newTask->next = head;
            head = newTask;
            return;
        }

        Task* current = head;
        while (current->next != nullptr && current->next->priority >= priority) {
            current = current->next;
        }

        newTask->next = current->next;
        current->next = newTask;
    }

    // Function to remove the highest priority task
    void removeHighestPriorityTask() {
        if (head == nullptr) {
            cout << "No tasks available to remove.\n";
            return;
        }

        Task* temp = head;
        head = head->next;
        delete temp;

        cout << "Highest priority task removed.\n";
    }

    // Function to remove a task by its ID
    void removeTaskById(int id) {
        if (head == nullptr) {
            cout << "No tasks available to remove.\n";
            return;
        }

        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task with ID " << id << " removed.\n";
            return;
        }

        Task* current = head;
        while (current->next != nullptr && current->next->id != id) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "Task with ID " << id << " not found.\n";
            return;
        }

        Task* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;

        cout << "Task with ID " << id << " removed.\n";
    }

    // Function to display all tasks
    void viewTasks() {
        if (head == nullptr) {
            cout << "No tasks available.\n";
            return;
        }

        cout << "Current Tasks:\n";
        for (Task* current = head; current != nullptr; current = current->next) {
            cout << "ID: " << current->id
                 << ", Description: " << current->description
                 << ", Priority: " << current->priority << "\n";
        }
    }

    ~TaskManager() {
        while (head != nullptr) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TaskManager manager;

    while (true) {
        cout << "\nTask Management System\n"
             << "1. Add Task\n"
             << "2. View Tasks\n"
             << "3. Remove Highest Priority Task\n"
             << "4. Remove Task by ID\n"
             << "5. Exit\n"
             << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 5) {
            cout << "Exiting program...\n";
            break;
        }

        int id, priority;
        string desc;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Task Description: ";
                getline(cin, desc);
                cout << "Enter Priority (higher number = higher priority): ";
                cin >> priority;
                manager.addTask(id, desc, priority);
                break;

            case 2:
                manager.viewTasks();
                break;

            case 3:
                manager.removeHighestPriorityTask();
                break;

            case 4:
                cout << "Enter Task ID to remove: ";
                cin >> id;
                manager.removeTaskById(id);
                break;

            default:
                cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
