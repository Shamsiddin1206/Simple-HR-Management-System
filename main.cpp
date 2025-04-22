#include <format>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#define WIDTH 100
using namespace std;

struct Employee {
    int id;
    string name;
    string position;
    int experience;
    double salary;
};

struct Applicant {
    int id;
    string name;
    string role;
    int experiences;
    vector<string> skills;
    double estimatedSalar;
};

struct Vacancy {
    int id;
    string position;
    int experienceYears;
    string salary;
    vector<string> keySkills;
    vector<Applicant> applicants;
};

vector<Employee> employees;
vector<Vacancy> vacancies;
int employeesID = 0;
int vacanciesID = 0;
int applicantsID = 0;

//----------Tools----------
void printCentered(const string &str);
Vacancy getVacancy(int id);

//----------Employee-----------
void addEmployee(Employee employee);
void fireEmployee(int id);
void listEmployees();
void updateEmployee(Employee newEmployee);

//----------Vacancies-----------
void addVacancy(Vacancy vacancy);
void deleteVacancy(int id);
void listVacancies();

//-----------HR Management System-----------
void greeting();
void HRSystem();
void applicantSystem();

int main() {
    greeting();
    return 0;
}

//-----------Tools----------
void printCentered(const string &str, bool state) {
    int margin = (WIDTH - str.length())/2;
    if (margin>0) {
        cout << string(margin, ' ') << str << string(margin, ' ');
        if (state) cout << endl;
    }
}

Vacancy getVacancy(int id) {
    for (auto vacancy : vacancies) {
        if (vacancy.id == id) {
            return vacancy;
        }
    }
    return {};
}


//----------Employee----------
void addEmployee(const string name, const string position, const double salary, const int experience) {
    Employee employee;
    employeesID++;
    employee.id = employeesID;
    employee.name = name;
    employee.position = position;
    employee.experience = experience;
    employee.salary = salary;
    employees.push_back(employee);
}

void fireEmployee(int id) {
    for (auto i = employees.begin(); i != employees.end(); ++i) {
        if (i->id==id) {
            employees.erase(i);
            printCentered("Successfully removed!", true);
            return;
        }
    }
}

void listEmployees() {
    if (employees.empty()) {
        cout << "You don't have any employee" << endl;
        return;
    }
    for (auto i = employees.begin(); i!=employees.end(); ++i) {
        ostringstream oss;
        oss << "ID: " << i->id
            << ", name: " << i->name
            << ", position: " << i->position
            << ", experience: " << i->experience
            << ", salary: " << i->salary;
        printCentered(oss.str(), true);
    }
}


//------------Vacancies------------
void listVacancies() {
    if (vacancies.empty()) {
        cout << "You don't have any vacancies" << endl;
        return;
    }
    for (auto & vacancy : vacancies) {
        ostringstream oss;
        oss << "ID: " << vacancy.id
            << ", position: " << vacancy.position
            << ", experience: " << vacancy.experienceYears
            << ", salary: " << vacancy.salary;
        printCentered(oss.str(), true);
    }
}


//-----------Systems----------
void greeting() {
    cout << "Welcome to our company's website!" << endl;
    cout << "----------Choose one option----------" << endl;
    cout << "1. I am looking for a job" << endl;
    cout << "2. I currently work there" << endl;
    cout << "3. Exit" << endl;
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
        case 3:
            return;
        default:
            printCentered("Invalid Input", true);
    }
}

void applicantSystem() {
    int vacancyCount = vacancies.size();

    cout << "Welcome!" << endl;
    cout << "What job you are looking for?" << endl;
    listVacancies();
    if (vacancies.empty()) {
        greeting();
    }
    cout << endl;

    cout << "Enter the id of vacancy" << endl;
    int errorOption = 0;
    bool inputState = true;

    int choice;
    do {
        cin >> choice;
        if (choice>vacancyCount) {
            inputState = false;
            errorOption++;
            cout << "No information found. Enter valid option" << endl;
            if (errorOption==3) {
                cout << "Error limit exceeded! Try again later" << endl;
                return;
            }
        }else {
            inputState = true;
        }
    } while (!inputState);

    Vacancy vacancy = getVacancy(choice);
    Applicant applicant;
    applicant.id = applicantsID++;

    cin.ignore();
    cout << "Name: " << endl;
    getline(cin, applicant.name);
    applicant.role = vacancy.position;
    cout << "Year of experience: " << endl;
    cin >> applicant.experiences;
    cout << "Estimated salary: " << endl;
    cin >> applicant.estimatedSalar;
    cout << "How many skills you want to enter? (max 5) " << endl;
    int temp;
    cin >> temp;
    if (temp>5) temp = 5;
    cin.ignore();
    for (int i = 1; i<=temp; i++){
        string ch;
        cout << i << " skill: " << endl;
        getline(cin, ch);
        if (!ch.empty()) {
            applicant.skills.push_back(ch);
        }else {
            cout << "Skill can not be empty!" << endl;
        }
    }
    if (!applicant.name.empty() && applicant.estimatedSalar>=0 && applicant.experiences>=0) {
        vacancy.applicants.push_back(applicant);
        cout << "Your application was sent!" << endl;
        cout << "Now return to Homepage!" << endl;
    }else {
        cout << "You need to answer to all questions" << endl;
        cout << "Try again later!" << endl;
    }
    greeting();
}

void HRSystem() {
    // printCentered("Welcome back!", true);
    // printCentered("----------HR Management Menu----------", true);
    // printCentered("1. Hire Employee", true);
    // printCentered("2. Fire Employee", true);
    // printCentered("3. Update Employee", true);
    // printCentered("4. List All Employees", true);
    // printCentered("5. Open new vacancy", true);
    // printCentered("6. Close vacancy", true);
    // printCentered("7. List all vacancies", true);
    // printCentered("8. Exit", true);
    bool state = true;
    while (state) {
        cout << endl;
        cout << "Welcome back!" << endl;
        cout << "HR Management Menu" << endl;
        cout << "1. Hire Employee" << endl;
        cout << "2. Fire Employee" << endl;
        cout << "3. Update Employee" << endl;
        cout << "4. List All Employees" << endl;
        cout << "5. Open new vacancy" << endl;
        cout << "6. Close vacancy" << endl;
        cout << "7. List all vacancies" << endl;
        cout << "8. Exit" << endl;
        int n;
        cin >> n;
        cin.ignore();
        switch (n) {
            case 1: {
                int id;
                cout << "Enter the id of vacancy: ";
                cin >> id;
                Vacancy vacancy = getVacancy(id);
                ostringstream oss;
                oss << "ID: " << vacancy.id
                    << ", position: " << vacancy.position
                    << ", experience: " << vacancy.experienceYears
                    << ", salary: " << vacancy.salary;
                printCentered(oss.str(), true);
                cout << endl;
                cout << "Choose a candidate" << endl;
                for (auto applicant : vacancy.applicants) {
                    ostringstream oss1;
                    oss1 << "ID: " << applicant.id
                        << ", role: " << applicant.role
                        << ", experience: " << applicant.experiences
                        << ", salary: " << applicant.estimatedSalar;
                    printCentered(oss1.str(), false);
                    for (auto i : applicant.skills) {
                        cout << i << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 2: {
                int id;
                cout << "ID: ";
                cin >> id;
                fireEmployee(id);
                break;
            }
            case 3: {
                printCentered("Currently unavailable", true);
                break;
            }
            case 4:
                listEmployees();
                break;
            case 5: {
                Vacancy vacancy;
                vacanciesID++;
                vacancy.id = vacanciesID;

                cout << "Position: " << endl;
                getline(cin, vacancy.position);

                cout << "Experience level (in years): ";
                cin >> vacancy.experienceYears;

                cout << "Salary: ";
                cin >> vacancy.salary;

                cout << "How many skills you want to enter? (max 5) " << endl;
                int temp;
                cin >> temp;
                if (temp>5) temp = 5;
                cin.ignore();
                for (int i = 1; i<=temp; i++){
                    string ch;
                    cout << i << " skill: " << endl;
                    getline(cin, ch);
                    if (!ch.empty()) {
                        vacancy.keySkills.push_back(ch);
                    }else {
                        cout << "Skill can not be empty!" << endl;
                    }
                }

                vacancies.push_back(vacancy);
                cout << "Successfully created!" << endl;
                break;
            }
            case 6: {
                int id;
                bool deleted = false;
                cin >> id;
                for (auto i = vacancies.begin(); i!=vacancies.end(); ++i) {
                    if (i->id == id) {
                        deleted = true;
                        vacancies.erase(i);
                        cout << "Successfully removed!" << endl;
                        break;
                    }
                }
                if (!deleted) cout << "Vacancy with this id does not exists!" << endl;
                break;
            }
            case 7:
                listVacancies();
                break;
            case 8:
                state = false;
                greeting();
                break;
            default:
                printCentered("Invalid Input", true);
                break;
        }
    }
}


