//
// Created by takhi on 4/23/2025.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

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
bool addVacancy();

void applicantSystem();

vector<Vacancy> vacanciesList;
vector<Applicant> applicantsList;
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
        cout << "0. Exit\n";
        cout << "================================\n";
        int choice;
        cout << "Enter your choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                cin.ignore();
                Vacancy vacancy;
                vacancy.id = vacancyID++;
                cout << "\nRole: \n";
                getline(cin, vacancy.role);
                cout << "\nSalary: \n";
                cin >> vacancy.salary;
                cout << "\nYear of Experience: \n";
                cin >> vacancy.experienceYear;

                if (vacancy.experienceYear>=0 && vacancy.salary>=0 && !vacancy.role.empty()) {
                    vacanciesList.push_back(vacancy);
                    cout << "\nSuccessfully created!\n";
                }else {
                    cout << "\nAll questions should be answered! Try again\n";
                }
                break;
            }
            case 2: {
                for (auto & v : vacanciesList) {
                    cout << "ID: " << v.id <<
                        "; Role: " << v.role <<
                            "; Experience Years: " << v.experienceYear <<
                                "; Salary: " << v.salary << endl;
                }
                break;
            }
            case 3: {
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
        for (auto & v : vacanciesList) {
            cout << "ID: " << v.id <<
                "; Role: " << v.role <<
                    "; Experience Years: " << v.experienceYear <<
                        "; Salary: " << v.salary << endl;
        }
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

                Vacancy v;
                bool found = false;
                for (auto i : vacanciesList) {
                    if (i.id == vID) {
                        v = i;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "No vacancy found. Try Again" << endl;
                    break;
                }else {
                    Applicant applicant;
                    applicant.id = applicantID++;
                    cin.ignore();
                    cout << "Name: ";
                    getline(cin, applicant.name);
                    cout << "Estimated Salary: ";
                    cin >> applicant.estimatedSalary;
                    cout << "Years of experience: ";
                    cin >> applicant.yearOfExperience;
                    applicant.vacancyID = vID;
                    applicant.position = v.role;
                    if (!applicant.name.empty() && applicant.estimatedSalary>=0 && applicant.yearOfExperience>=0) {
                        applicantsList.push_back(applicant);
                        cout << "Your applicant was sent!" << endl;
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


