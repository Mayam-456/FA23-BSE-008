#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Patient {
    string patientName;
    string emergencyCondition;
    int priority;
    int arrivalOrder;

    Patient(string name, string condition, int prio, int order)
        : patientName(name), emergencyCondition(condition), priority(prio), arrivalOrder(order) {}
};

struct PatientPriority {
    bool operator()(const Patient& a, const Patient& b) {
        if (a.priority == b.priority)
            return a.arrivalOrder > b.arrivalOrder;
        return a.priority > b.priority;
    }
};

int determinePriority(const string& emergencyCondition) {
    if (emergencyCondition == "Heart Attack" || emergencyCondition == "Stroke") return 1;
    if (emergencyCondition == "Broken Leg" || emergencyCondition == "Severe Burn" || emergencyCondition == "Fractured Arm") return 2;
    if (emergencyCondition == "Fever" || emergencyCondition == "Food Poisoning" || emergencyCondition == "Migraine") return 3;
    return 4;
}

void printTreatmentQueue(priority_queue<Patient, vector<Patient>, PatientPriority> queue) {
    while (!queue.empty()) {
        Patient current = queue.top();
        queue.pop();
        cout << current.patientName << " | " << current.emergencyCondition << " | Priority: " << current.priority << "\n";
    }
}

int main() {
    priority_queue<Patient, vector<Patient>, PatientPriority> patientQueue;
    int arrivalOrder = 1;
    int menuChoice;

    do {
        cout << "\n=== Emergency Room Patient Queue ===\n";
        cout << "1. Add New Patient\n";
        cout << "2. View Current Queue\n";
        cout << "3. Exit and Show Final Order\n";
        cout << "Select an option: ";
        cin >> menuChoice;
        cin.ignore();

        if (menuChoice == 1) {
            string patientName, emergencyCondition;
            cout << "Enter Patient Name: ";
            getline(cin, patientName);
            cout << "Enter Emergency Condition: ";
            getline(cin, emergencyCondition);

            int priority = determinePriority(emergencyCondition);
            Patient newPatient(patientName, emergencyCondition, priority, arrivalOrder++);
            patientQueue.push(newPatient);
            cout << "Patient added to the queue.\n";
        }
        else if (menuChoice == 2) {
            if (patientQueue.empty()) {
                cout << "No patients currently waiting.\n";
            } else {
                cout << "\n--- Current Treatment Queue ---\n";
                printTreatmentQueue(patientQueue);
            }
        }
        else if (menuChoice == 3) {
            cout << "\n--- Final Treatment Order ---\n";
            if (patientQueue.empty()) {
                cout << "No patients in the queue.\n";
            } else {
                printTreatmentQueue(patientQueue);
            }
            cout << "Thank you. Exiting system...\n";
        }
        else {
            cout << "Invalid selection. Please try again.\n";
        }

    } while (menuChoice != 3);

    return 0;
}
