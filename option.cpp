#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Employee {
    int id;
    string name;
    string position;
    double salary;
    int experience;
};

struct Vacancy {
    int id;
    string role;
    double salary;
    int experienceYear;
};

struct Applicant {
    int id;
    string name;
    int yearOfExperience;
    double estimatedSalary;
    string position;
    int vacancyID;
};

// Global variables for ID tracking
int employeeID = 0;
int vacancyID = 0;
int applicantID = 0;

// File names
const string vacancyFile = "vacancies.txt";
const string applicantFile = "applicants.txt";
const string employeeFile = "employees.txt";

// Function declarations
void greeting();
void HRSystem();
void addVacancy();
void listAllVacancies();
void deleteVacancy();
bool checkVacancy(int id);
Vacancy getVacancyByID(int vID);
void removeVacancy(int vID);

void applicantSystem();
vector<Applicant> getApplicantsOfVacancy(int vID);
void listApplicants(const vector<Applicant>& applications);
bool checkApplicant(int aID, const vector<Applicant>& applications);
Applicant getApplicantByID(int aID);

void listAllEmployees();
void saveVacancies();
void loadVacancies();
void saveApplicants();
void loadApplicants();
void saveEmployees();
void loadEmployees();

vector<Vacancy> vacanciesList;
vector<Applicant> applicantsList;
vector<Employee> employees;

// Main function
int main() {
    // Load data from files
    loadVacancies();
    loadApplicants();
    loadEmployees();

    greeting();
}

// Greeting function
void greeting() {
    cout << "\n===== Homepage =====\n";
    cout << "1. Apply for a job\n";
    cout << "2. Login to HR Account\n";
    cout << "0. Exit\n";
    cout << "================================\n";

    int n;
    cout << "Enter your choice: " << endl;
    cin >> n;
    switch (n) {
        case 1:
            applicantSystem();
            break;
        case 2:
            HRSystem();
            break;
        case 0:
            break;
        default:
            cout << "Invalid Input! Try again\n";
            greeting();
            break;
    }
}

// HR System for HR management
void HRSystem() {
    bool state = true;
    while (state) {
        cout << "\n===== HR MANAGEMENT SYSTEM =====\n";
        cout << "1. Open new vacancy\n";
        cout << "2. Check Vacancies\n";
        cout << "3. Delete vacancy\n";
        cout << "4. Hire an employee\n";
        cout << "5. List All employees\n";
        cout << "0. Exit\n";
        cout << "================================\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addVacancy();
                break;
            case 2:
                if (vacanciesList.empty()) {
                    cout << "No vacancies found\n";
                } else {
                    listAllVacancies();
                }
                break;
            case 3:
                deleteVacancy();
                break;
            case 4:
                if (vacanciesList.empty()) {
                    cout << "Currently no open vacancies. You cannot hire.\n";
                    break;
                }
                cout << "\n===== Vacancies List =====\n";
                listAllVacancies();
                cout << "================================\n";
                int vID;
                cout << "Which vacancy? (ID) ";
                cin >> vID;

                if (checkVacancy(vID)) {
                    vector<Applicant> applications = getApplicantsOfVacancy(vID);
                    if (applications.empty()) {
                        cout << "No applications received!\n";
                        break;
                    }
                    listApplicants(applications);
                    int aID;
                    cout << "Choose a candidate (ID): ";
                    cin >> aID;
                    if (checkApplicant(aID, applications)) {
                        Applicant applicant = getApplicantByID(aID);
                        Employee employee;
                        employeeID++;
                        employee.id = employeeID;
                        employee.name = applicant.name;
                        employee.salary = applicant.estimatedSalary;
                        employee.position = applicant.position;
                        employee.experience = applicant.yearOfExperience;
                        employees.push_back(employee);
                        cout << "Successfully hired!\n";
                        removeVacancy(vID);
                        saveEmployees();
                        break;
                    }
                } else {
                    cout << "No vacancy found. Enter a valid ID!\n";
                    break;
                }
            case 5:
                listAllEmployees();
                break;
            case 0:
                state = false;
                greeting();
                break;
            default:
                cout << "Invalid Input\n";
        }
    }
}

// Applicant System
void applicantSystem() {
    bool state = true;
    while (state) {
        cout << "\n===== Vacancies List =====\n";
        if (vacanciesList.empty()) {
            cout << "Currently no open vacancies!\n";
            state = false;
            greeting();
        }
        listAllVacancies();
        cout << "================================\n";
        cout << "1. Apply\n";
        cout << "0. Exit\n";
        cout << "================================\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cin.ignore();
                int vID;
                cout << "Vacancy ID: ";
                cin >> vID;

                if (!checkVacancy(vID)) {
                    cout << "No vacancy found. Try Again\n";
                    break;
                } else {
                    const Vacancy v = getVacancyByID(vID);
                    Applicant applicant;
                    applicantID++;
                    applicant.id = applicantID;
                    cin.ignore();
                    cout << "Name: ";
                    getline(cin, applicant.name);
                    cout << "Estimated Salary: ";
                    cin >> applicant.estimatedSalary;
                    cout << "Years of experience: ";
                    cin >> applicant.yearOfExperience;
                    applicant.vacancyID = vID;
                    applicant.position = v.role;
                    if (!applicant.name.empty() && applicant.estimatedSalary >= 0 && applicant.yearOfExperience >= 0) {
                        applicantsList.push_back(applicant);
                        saveApplicants();
                        cout << "Your application was sent!\n";
                    } else {
                        cout << "You need to answer all questions. Try again later.\n";
                    }
                    break;
                }
            case 0:
                state = false;
                cout << endl;
                greeting();
                break;
            default:
                cout << "Invalid Input!\n";
        }
    }
}

// List all vacancies
void listAllVacancies() {
    for (const auto& v : vacanciesList) {
        cout << "ID: " << v.id
             << "; Role: " << v.role
             << "; Experience Years: " << v.experienceYear
             << "; Salary: " << v.salary << endl;
    }
}

// Add a new vacancy
void addVacancy() {
    cin.ignore();
    Vacancy vacancy;
    vacancyID++;
    vacancy.id = vacancyID;
    cout << "Role: ";
    getline(cin, vacancy.role);
    cout << "Salary: ";
    cin >> vacancy.salary;
    cout << "Year of Experience: ";
    cin >> vacancy.experienceYear;

    if (vacancy.experienceYear >= 0 && vacancy.salary >= 0 && !vacancy.role.empty()) {
        vacanciesList.push_back(vacancy);
        saveVacancies();
        cout << "\nSuccessfully created vacancy!\n";
    } else {
        cout << "\nAll questions should be answered! Try again\n";
    }
}

// Delete a vacancy
void deleteVacancy() {
    int id;
    bool deleted = false;
    cout << "ID: ";
    cin >> id;
    for (auto it = vacanciesList.begin(); it != vacanciesList.end(); ++it) {
        if (it->id == id) {
            vacanciesList.erase(it);
            deleted = true;
            break;
        }
    }
    if (deleted) {
        cout << "Removed successfully!\n";
        saveVacancies();
    } else {
        cout << "Could not find vacancy. Try again later.\n";
    }
}

// Check if a vacancy exists by ID
bool checkVacancy(int vID) {
    for (auto& i : vacanciesList) {
        if (i.id == vID) {
            return true;
        }
    }
    return false;
}

// Get a vacancy by ID
Vacancy getVacancyByID(int vID) {
    for (auto& i : vacanciesList) {
        if (i.id == vID) {
            return i;
        }
    }
    return Vacancy();  // Return default object if not found
}

// Remove a vacancy by ID
void removeVacancy(int vID) {
    for (auto it = vacanciesList.begin(); it != vacanciesList.end(); ++it) {
        if (it->id == vID) {
            vacanciesList.erase(it);
            cout << "Successfully closed the vacancy!\n";
            saveVacancies();
            return;
        }
    }
}

// Get applicants of a specific vacancy
vector<Applicant> getApplicantsOfVacancy(int vID) {
    vector<Applicant> applications;
    for (const auto& i : applicantsList) {
        if (i.vacancyID == vID) {
            applications.push_back(i);
        }
    }
    return applications;
}

// List all applicants for a vacancy
void listApplicants(const vector<Applicant>& applications) {
    cout << "\n===== Applicants List =====\n";
    for (const auto& i : applications) {
        cout << "ID: " << i.id << "; Name: " << i.name << "; Estimated Salary: " << i.estimatedSalary
             << "; Experience: " << i.yearOfExperience << " years\n";
    }
}

// Check if an applicant exists by ID
bool checkApplicant(int aID, const vector<Applicant>& applications) {
    for (const auto& i : applications) {
        if (i.id == aID) {
            return true;
        }
    }
    return false;
}

// Get an applicant by ID
Applicant getApplicantByID(int aID) {
    for (auto& i : applicantsList) {
        if (i.id == aID) {
            return i;
        }
    }
    return Applicant();
}

// List all employees
void listAllEmployees() {
    cout << "\n===== Employees List =====\n";
    for (const auto& e : employees) {
        cout << "ID: " << e.id << "; Name: " << e.name << "; Position: " << e.position
             << "; Salary: " << e.salary << "; Experience: " << e.experience << endl;
    }
}

// Load vacancies from file
void loadVacancies() {
    ifstream file(vacancyFile);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Vacancy vacancy;
        string token;
        getline(ss, token, ','); vacancy.id = stoi(token);
        getline(ss, vacancy.role, ',');
        getline(ss, token, ','); vacancy.salary = stod(token);
        getline(ss, token, ','); vacancy.experienceYear = stoi(token);
        vacanciesList.push_back(vacancy);
    }
    file.close();
}

// Load applicants from file
void loadApplicants() {
    ifstream file(applicantFile);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Applicant applicant;
        string token;
        getline(ss, token, ','); applicant.id = stoi(token);
        getline(ss, applicant.name, ',');
        getline(ss, token, ','); applicant.yearOfExperience = stoi(token);
        getline(ss, token, ','); applicant.estimatedSalary = stod(token);
        getline(ss, applicant.position, ',');
        getline(ss, token, ','); applicant.vacancyID = stoi(token);
        applicantsList.push_back(applicant);
    }
    file.close();
}

// Load employees from file
void loadEmployees() {
    ifstream file(employeeFile);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Employee employee;
        string token;
        getline(ss, token, ','); employee.id = stoi(token);
        getline(ss, employee.name, ',');
        getline(ss, employee.position, ',');
        getline(ss, token, ','); employee.salary = stod(token);
        getline(ss, token, ','); employee.experience = stoi(token);
        employees.push_back(employee);
    }
    file.close();
}

// Save vacancies to file
void saveVacancies() {
    ofstream file(vacancyFile);
    for (const auto& v : vacanciesList) {
        file << v.id << ","
             << v.role << ","
             << v.salary << ","
             << v.experienceYear << endl;
    }
    file.close();
}

// Save applicants to file
void saveApplicants() {
    ofstream file(applicantFile);
    for (const auto& a : applicantsList) {
        file << a.id << ","
             << a.name << ","
             << a.yearOfExperience << ","
             << a.estimatedSalary << ","
             << a.position << ","
             << a.vacancyID << endl;
    }
    file.close();
}

// Save employees to file
void saveEmployees() {
    ofstream file(employeeFile);
    for (const auto& e : employees) {
        file << e.id << ","
             << e.name << ","
             << e.position << ","
             << e.salary << ","
             << e.experience << endl;
    }
    file.close();
}
