#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <windows.h>

using namespace std;

string password;
class Students {
protected:
    string name, number, id;

public:
    Students() { // Constructor
        srand(time(NULL));
        name = "";
        number = "";
        int num = rand() % 8999 + 1000;
        id = to_string(num);
    }

    void set_name() { // Set Name
        cin >> name;
    }

    void set_number() { // Set Number
        cin >> number;
    }

    void set_data() { // Set All Data
        string x, y;
        cout << "\nPlease Enter student name: ";
        cin.ignore();
        getline(cin, x);
        name = x;
        cout << "\nPlease Enter student number: ";
        cin >> y;
        number = y;
    }

    void set_new_id() {
        srand(time(NULL));
        id = to_string(rand() % 8999 + 1000);
    }

    string get_name() { // Get Name
        return name;
    }

    string get_number() { // Get Number
        return number;
    }

    string get_id() { // Get id
        return id;
    }

    void print() { // Print Student Details(Name, Number, id)
        cout << "Student Details-->  1-Student ID : " << id << endl;
        cout << "                    2-Student Name : " << name << endl;
        cout << "                    3-Student Number : " << number << endl;
    }
};

void login();
void menu();
void search();
void delete_record();
void profit();
void add_record();
void show_record();
void change_pass();

int main() {
    login();
    return 0;
}

void login() {
    ifstream input("password.txt");
    if (!input) {
        cerr << "Error opening password file." << endl;
        exit(1);
    }
    input >> password;
    input.close();

    int count = 0;
    while (true) {
        string pass;
        cout << "\t\t\t\t\tWelcome To Levai Center (:\n\n\n\t\t\t\t\t     Enter Password: ";
        cin >> pass;
        if (pass == password) {
            system("cls");
            menu();
        } else if (count == 2) {
            cout << "Attempt Limit Reached! Exiting...\n";
            exit(2);
        }
        count++;
        system("cls");
    }
}

void menu() { // Main screen
    int option;
    do {
        cout << "\t\t\t\t\tMAIN MENU\n-->PLEASE ENTER NUMBER";
        cout << "\n1-To Add Record.\n2-To Show Record.\n3-To Search Record.\n4-To Show Profit.\n5-To Delete Record.\n6-To Change Password.\n==> ";
        cin >> option;
        cout << "<====Any Other Key To Exit====>\n";
        switch (option) {
            case 1:
                system("cls");
                add_record();
                break;
            case 2:
                system("cls");
                show_record();
                break;
            case 3:
                system("cls");
                search();
                break;
            case 4:
                system("cls");
                profit();
                break;
            case 5:
                system("cls");
                delete_record();
                break;
            case 6:
                system("cls");
                change_pass();
                break;
            default:
                exit(5);
                break;
        }
        system("cls");
    } while (true);
}

void search() {
    string id, c, first_line;
    ifstream file("students.txt");
    if (!file) {
        cerr << "Cannot open file." << endl;
        return;
    }

    cout << "Enter student's id you want to search: ";
    cin >> id;

    bool found = false;
    while (getline(file, c)) {
        if (c.substr(0, 4) == id) { // Assuming ID is the first 4 characters
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Not found.\nEnter any key to return to the main menu\n";
        system("pause");
        return;
    }

    cout << "Show record?(y/n) ";
    char op;
    cin >> op;
    if (op == 'y' || op == 'Y') {
        file.clear();
        file.seekg(0, ios::beg);
        while (getline(file, c)) {
            if (c.substr(0, 4) == id) {
                cout << c << endl;
                break;
            }
        }
    }
    cout << "\nEnter any key to return to the main menu\n";
    system("pause");
    file.close();
}

void show_record() { // Print student data
    ifstream student("students.txt");
    if (!student) {
        cerr << "Cannot open file." << endl;
        return;
    }

    string data;
    while (getline(student, data)) {
        cout << data << endl;
    }
    cout << "Enter any key to return to the Main menu\n";
    system("pause");
    student.close();
}

void profit() {
    ifstream student("students.txt");
    if (!student) {
        cerr << "Cannot open file." << endl;
        return;
    }

    string data;
    long total = 0;
    while (student >> data) {
        if (data == "Yes") {
            total += 20;
        }
    }
    cout << "Total Profit: " << total << "\nEnter any key to return to the main menu\n";
    system("pause");
    student.close();
}

void add_record() {
    ofstream student("students.txt", ios::app);
    if (!student) {
        cerr << "Cannot open file." << endl;
        return;
    }

    Students s;
    s.set_data();
    string id = s.get_id();
    id.resize(10, ' ');
    student << id;

    string name = s.get_name();
    name.resize(20, ' ');
    student << name;

    string number = s.get_number();
    number.resize(15, ' ');
    student << number;

    string subjects[5] = { "No", "No", "No", "No", "No" };
    int op;

    while (true) {
        cout << "Subjects you want to book:\n1-Arabic\t100L.E(80+20)\n2-English\t100L.E(80+20)\n3-Physics\t100L.E(80+20)\n4-Math\t100L.E(80+20)\n5-Chemistry\t100L.E(80+20)\n6-Book\n==>";
        cin >> op;
        if (op >= 1 && op <= 5) {
            subjects[op - 1] = "Yes";
        } else if (op == 6) {
            break;
        }
        system("cls");
    }

    for (int i = 0; i < 5; i++) {
        string subject = subjects[i];
        subject.resize(10, ' ');
        student << subject;
    }
    student << endl;
    student.close();
    cout << "Booking successfully! Your ID is: " << s.get_id() << endl;
    cout << "Enter any key to return to the main screen\n";
    system("pause");
}

void delete_record() { // Delete student record
    string id;
    cout << "Enter the ID you want to delete: ";
    cin >> id;

    ifstream students("students.txt");
    if (!students) {
        cerr << "Cannot open file." << endl;
        return;
    }

    ofstream tempstudents("tempstudents.txt", ios::out | ios::trunc);
    if (!tempstudents) {
        cerr << "Cannot open file." << endl;
        return;
    }

    string line;
    while (getline(students, line)) {
        if (line.substr(0, 4) != id) { // Assuming ID is the first 4 characters
            tempstudents << line << endl;
        }
    }
    students.close();
    tempstudents.close();

    if (remove("students.txt") != 0 || rename("tempstudents.txt", "students.txt") != 0) {
        cerr << "Error updating records." << endl;
    } else {
        cout << "Record with ID " << id << " deleted successfully." << endl;
    }
    cout << "Enter any key to return to the main menu.\n";
    system("pause");
}

void change_pass() {
    string current_pass, new_pass, confirm_pass;
    cout << "Enter Current Password: ";
    cin >> current_pass;

    if (current_pass != password) {
        cout << "Current password is incorrect.\n";
        return;
    }

    do {
        cout << "Enter New Password: ";
        cin >> new_pass;
        cout << "Re-Enter New Password: ";
        cin >> confirm_pass;

        if (new_pass != confirm_pass) {
            cout << "Passwords do not match. Enter Y to try again or any other key to go back to the main menu: ";
            char choice;
            cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                return;
            }
        }
    } while (new_pass != confirm_pass);

    ofstream out("password.txt", ios::trunc);
    if (!out) {
        cerr << "Cannot open file." << endl;
        return;
    }
    out << new_pass;
    out.close();
    password = new_pass; // Update the password variable
    cout << "Password changed successfully.\nEnter any key to return to the main menu.";
    system("pause");
}

