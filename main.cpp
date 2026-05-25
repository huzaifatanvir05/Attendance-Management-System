#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

// Function declarations
void addStudent(int*& ids, string*& names, int*& att, int& count);
void markAttendance(int* att, string* names, int count);
void display(int* ids, string* names, int* att, int count);
void updateAttendance(int* ids, int* att, int count);

int main() {
    int* ids = nullptr;
    string* names = nullptr;
    int* attendance = nullptr;

    int studentCount = 0;
    int choice;

    do {
        cout << "\n--- Student Attendance System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. Display Attendance\n";
        cout << "4. Update Attendance\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent(ids, names, attendance, studentCount);
            break;
        case 2:
            markAttendance(attendance, names, studentCount);
            break;
        case 3:
            display(ids, names, attendance, studentCount);
            break;
        case 4:
            updateAttendance(ids, attendance, studentCount);
            break;
        case 5:
            cout << "Program ended.\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    delete[] ids;
    delete[] names;
    delete[] attendance;

    _getch();
    return 0;
}

// Add student (duplicate roll number check)
void addStudent(int*& ids, string*& names, int*& att, int& count) {
    int* newIds = new int[count + 1];
    string* newNames = new string[count + 1];
    int* newAtt = new int[count + 1];

    for (int i = 0; i < count; i++) {
        newIds[i] = ids[i];
        newNames[i] = names[i];
        newAtt[i] = att[i];
    }

    int newId;
    bool duplicate;

    do {
        duplicate = false;
        cout << "Enter Student Roll Number: ";
        cin >> newId;

        for (int i = 0; i < count; i++) {
            if (ids[i] == newId) {
                cout << "Error: Roll number already exists. Try again.\n";
                duplicate = true;
                break;
            }
        }
    } while (duplicate);

    newIds[count] = newId;

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, newNames[count]);

    newAtt[count] = 0;

    delete[] ids;
    delete[] names;
    delete[] att;

    ids = newIds;
    names = newNames;
    att = newAtt;

    count++;
    cout << "Student added successfully!\n";
}

// Mark attendance (P/A)
void markAttendance(int* att, string* names, int count) {
    if (count == 0) {
        cout << "No students available.\n";
        return;
    }

    char status;
    for (int i = 0; i < count; i++) {
        cout << "Is " << names[i] << " present? (P/A): ";
        cin >> status;

        if (status == 'P' || status == 'p')
            att[i] = 1;
        else
            att[i] = 0;
    }
}

// Display attendance (P/A)
void display(int* ids, string* names, int* att, int count) {
    if (count == 0) {
        cout << "No data to display.\n";
        return;
    }

    cout << "\nRoll No\tName\tAttendance\n";
    for (int i = 0; i < count; i++) {
        cout << ids[i] << "\t" << names[i] << "\t";
        cout << (att[i] == 1 ? "P" : "A") << endl;
    }
}

// Update attendance (FIXED — no infinite loop)
void updateAttendance(int* ids, int* att, int count) {
    if (count == 0) {
        cout << "No students available.\n";
        return;
    }

    int id;
    char status;

    cout << "Enter student roll number: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (ids[i] == id) {
            cout << "Enter attendance (P/A): ";
            cin >> status;

            if (status == 'P' || status == 'p')
                att[i] = 1;
            else
                att[i] = 0;

            cout << "Attendance updated successfully.\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

