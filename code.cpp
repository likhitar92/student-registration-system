#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <sstream>
#include <cstdlib>

using namespace std;

struct Student {
    int id;
    string name;
    string gender;
    string department;
    int age;
    string password;               // Password added
    vector<string> clubs;
};

vector<Student> students;

// Trim function
string trim(string s) {
    int start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    int end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Parse club list
vector<string> parseClubs(string line) {
    vector<string> out;
    stringstream ss(line);
    string item;
    while (getline(ss, item, ',')) {
        string t = trim(item);
        if (!t.empty()) out.push_back(t);
    }
    return out;
}

// Add student
void addStudent() {
    Student s;

    cout << "Enter Student ID: ";
    while (!(cin >> s.id)) {
        cout << "Invalid input. Enter numeric Student ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Gender: ";
    getline(cin, s.gender);

    cout << "Enter Department: ";
    getline(cin, s.department);

    cout << "Enter Age: ";
    while (!(cin >> s.age)) {
        cout << "Invalid input. Enter numeric age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Create Password: ";
    getline(cin, s.password);

    cout << "Enter Club Activities (comma-separated or press Enter for none): ";
    string clubsLine;
    getline(cin, clubsLine);
    s.clubs = parseClubs(clubsLine);

    students.push_back(s);
    cout << "Student added successfully!\n";
}

// Print student brief
void printStudentBrief(const Student &s) {
    cout << "ID: " << s.id
         << ", Name: " << s.name
         << ", Gender: " << s.gender
         << ", Department: " << s.department
         << ", Age: " << s.age << endl;
}

// Print full student
void printStudentFull(const Student &s) {
    printStudentBrief(s);
    cout << "Club Activities: ";
    if (s.clubs.empty()) {
        cout << "None\n";
    } else {
        for (int i = 0; i < (int)s.clubs.size(); i++) {
            cout << s.clubs[i];
            if (i + 1 < (int)s.clubs.size()) cout << " | ";
        }
        cout << endl;
    }
}

// Display all students
void displayStudents() {
    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }

    cout << "\nRegistered Students:\n";
    for (int i = 0; i < (int)students.size(); i++) {
        printStudentBrief(students[i]);
    }
}

// Search student
void searchStudent() {
    int id;
    cout << "Enter Student ID to search: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter numeric ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].id == id) {
            cout << "Student found:\n";
            printStudentFull(students[i]);
            return;
        }
    }
    cout << "Student not found.\n";
}

// Update student
void updateStudent() {
    int id;
    cout << "Enter Student ID to update: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter numeric ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].id == id) {
            string tmp;

            cout << "Enter New Name (press Enter to keep old): ";
            getline(cin, tmp);
            if (!tmp.empty()) students[i].name = tmp;

            cout << "Enter New Gender (press Enter to keep old): ";
            getline(cin, tmp);
            if (!tmp.empty()) students[i].gender = tmp;

            cout << "Enter New Department (press Enter to keep old): ";
            getline(cin, tmp);
            if (!tmp.empty()) students[i].department = tmp;

            cout << "Enter New Age (press Enter to keep old): ";
            string ageLine;
            getline(cin, ageLine);
            if (!ageLine.empty()) {
                int newAge = atoi(ageLine.c_str());
                if (newAge > 0) students[i].age = newAge;
            }

            cout << "Change Password (press Enter to keep old): ";
            getline(cin, tmp);
            if (!tmp.empty()) students[i].password = tmp;

            cout << "Enter New Club Activities (comma-separated or press Enter to keep old): ";
            string clubsLine;
            getline(cin, clubsLine);
            if (!clubsLine.empty()) {
                students[i].clubs = parseClubs(clubsLine);
            }

            cout << "Student updated successfully!\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// Delete student
void deleteStudent() {
    int id;
    cout << "Enter Student ID to delete: ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter numeric ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].id == id) {
            students.erase(students.begin() + i);
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

// Login function with password
void loginAndViewDetails() {
    int id;
    string pass;

    cout << "Enter Registration Number (Student ID): ";
    while (!(cin >> id)) {
        cout << "Invalid input. Enter numeric ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Enter Password: ";
    getline(cin, pass);

    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].id == id && students[i].password == pass) {
            cout << "\nLogin successful!\n";
            printStudentFull(students[i]);
            return;
        }
    }
    cout << "\nInvalid ID or Password!\n";
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n--- Student Registration Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student Record\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Login (View Details)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Enter numeric choice: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: loginAndViewDetails(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while(choice != 0);

    return 0;
}
