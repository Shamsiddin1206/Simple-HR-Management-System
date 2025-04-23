//
// Created by takhi on 4/23/2025.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Employee {
    int id;
    string name;
    string position;
    double salary;
    int experience;
};
int employeeID = 0;

struct Vacancy{
    int id;
    string role;
    double salary;
    int experienceYear;
};
int vacancyID = 0;

struct Applicant {
    int id;
    string name;
    int yearOfExperience;
    double estimatedSalary;
    string position;
    int vacancyID;
};
int applicantID = 0;

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
void listApplicants(const vector<Applicant> &applications);
bool checkApplicant(int aID, const vector<Applicant> &applications);
Applicant getApplicantByID(int aID);

void listAllEmployees();

vector<Vacancy> vacanciesList;
vector<Applicant> applicantsList;
vector<Employee> employees;
int main() {
    greeting();
}

void greeting() {
    cout << "\n===== Homepage =====\n";
    cout << "1. Apply for a job" << endl;
    cout << "2. Login to HR Account" << endl;
    cout << "0. Exit" << endl;
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
            cout << "Invalid Input! Try again" << endl;
    }
}


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
        cout << "Enter your choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                addVacancy();
                break;
            }
            case 2: {
                if (vacanciesList.empty()) {
                    cout << "No vacancies found" << endl;
                }else {
                    listAllVacancies();
                }
                break;
            }
            case 3: {
                deleteVacancy();
                break;
            }
            case 4: {
                if (vacanciesList.empty()) {
                    cout << "Currently no open vacancies. You can not hire." << endl;
                    break;
                }
                cout << "\n===== Vacancies List =====\n";
                listAllVacancies();
                cout << "================================\n";
                int vID;
                cout << "Which vacancy? (ID) \n";
                cin >> vID;

                if (checkVacancy(vID)) {
                    vector<Applicant> applications = getApplicantsOfVacancy(vID);
                    if (applications.empty()) {
                        cout << "No applications received!" << endl;
                        break;
                    }
                    listApplicants(applications);
                    int aID;
                    cout << "Choose a candidate (ID): " << endl;
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
                        cout << "Successfully hired!" << endl;
                        removeVacancy(vID);
                        break;
                    }
                }else {
                    cout << "No vacancy found. Enter valid ID!" << endl;
                    break;
                }
            }
            case 5: {
                listAllEmployees();
                break;
            }
            case 0:
                state = false;
                greeting();
                break;
            default:
                cout << "Invalid Input" << endl;
        }
    }
}

void applicantSystem() {
    bool state = true;
    while (state) {
        cout << "\n===== Vacancies List =====\n";
        if (vacanciesList.empty()) {
            cout << "Currently no open vacancies!" << endl;
            state = false;
            greeting();
        }
        listAllVacancies();
        cout << "================================\n";
        cout << "1. Apply" << endl;
        cout << "0. Exit" << endl;
        cout << "================================\n";

        int choice;
        cout << "Enter your choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                cin.ignore();
                int vID;
                cout << "Vacancy ID: " << endl;
                cin >> vID;

                if (!checkVacancy(vID)) {
                    cout << "No vacancy found. Try Again" << endl;
                    break;
                }else {
                    const Vacancy v = getVacancyByID(vID);
                    Applicant applicant;
                    applicantID++;
                    applicant.id = applicantID;
                    cin.ignore();
                    cout << "Name: \n";
                    getline(cin, applicant.name);
                    cout << "Estimated Salary: \n";
                    cin >> applicant.estimatedSalary;
                    cout << "Years of experience: \n";
                    cin >> applicant.yearOfExperience;
                    applicant.vacancyID = vID;
                    applicant.position = v.role;
                    if (!applicant.name.empty() && applicant.estimatedSalary>=0 && applicant.yearOfExperience>=0) {
                        applicantsList.push_back(applicant);
                        cout << "Your application was sent!" << endl;
                    }else {
                        cout << "You need to answer to all questions. Try again later." << endl;
                    }
                    break;
                }
            }
            case 0:
                state = false;
                cout << endl;
                greeting();
                break;
            default:
                cout << "Invalid Input!" << endl;
        }
    }

}

void listAllVacancies() {
    for (auto & v : vacanciesList) {
        cout << "ID: " << v.id <<
            "; Role: " << v.role <<
                "; Experience Years: " << v.experienceYear <<
                    "; Salary: " << v.salary << endl;
    }
}
void addVacancy() {
    cin.ignore();
    Vacancy vacancy;
    vacancyID++;
    vacancy.id = vacancyID;
    cout << "Role: \n";
    getline(cin, vacancy.role);
    cout << "Salary: \n";
    cin >> vacancy.salary;
    cout << "Year of Experience: \n";
    cin >> vacancy.experienceYear;

    if (vacancy.experienceYear>=0 && vacancy.salary>=0 && !vacancy.role.empty()) {
        vacanciesList.push_back(vacancy);
        cout << "\nSuccessfully created!\n";
    }else {
        cout << "\nAll questions should be answered! Try again\n";
    }
}
void deleteVacancy() {
    int id;
    bool deleted = false;
    cout << "ID: " << endl;
    cin >> id;
    for (auto i = vacanciesList.begin(); i!=vacanciesList.end(); ++i) {
        if (i->id == id) {
            vacanciesList.erase(i);
            deleted = true;
            break;
        }
    }
    if (deleted) {
        cout << "Removed successfully!" << endl;
    }else {
        cout << "Could not find vacancy. Try again later." << endl;
    }
}
bool checkVacancy(const int vID) {
    for (auto i : vacanciesList) {
        if (i.id == vID) {
            return true;
        }
    }
    return false;
}
Vacancy getVacancyByID(const int vID) {
    for (auto i : vacanciesList) {
        if (i.id == vID) {
            return i;
        }
    }
    return {};
}
void removeVacancy(int vID) {
    for (auto i = vacanciesList.begin(); i!=vacanciesList.end(); ++i) {
        if (i->id == vID) {
            vacanciesList.erase(i);
            cout << "Successfully closed the vacancy!" << endl;
            return;
        }
    }
}


vector<Applicant> getApplicantsOfVacancy(const int vID) {
    vector<Applicant> applications;
    for (const auto& i : applicantsList) {
        if (i.vacancyID == vID) {
            applications.push_back(i);
        }
    }
    return applications;
}
void listApplicants(const vector<Applicant>& applications) {
    cout << "\n===== Applicants List =====\n";
    for (const auto& i : applications) {
        cout << "ID: " << i.id <<
            "; Name: " << i.name <<
                "; Experience: " << i.yearOfExperience <<
                    "; Estimated Salary: " << i.estimatedSalary << endl;
    }
    cout << "================================\n";
}
bool checkApplicant(const int aID, const vector<Applicant> &applications) {
    for (const auto& i : applications) {
        if (i.id == aID) {
            return true;
        }
    }
    return false;
}
Applicant getApplicantByID(const int aID) {
    for (auto i : applicantsList) {
        if (i.id == aID) {
            return i;
        }
    }
    return {};
}

void listAllEmployees() {
    for (auto i : employees) {
        cout << "ID: " << i.id <<
            "; Name: " << i.name <<
                "; Position: " << i.position <<
                    "; Salary: " << i.salary <<
                        "; Experience (Years): " << i.experience << endl;
    }
}












