// //
// // Created by takhi on 4/22/2025.
// //
// #include <iostream>
// #include <string>
// #include <fstream>
// #include <limits>
//
// using namespace std;
//
// // Constants
// const int MAX_EMPLOYEES = 100;
// const string FILE_NAME = "employee_data.txt";
//
// // Function prototypes
// void displayMenu();
// void hireEmployee(int employeeIds[], string employeeNames[], int employeeAges[],
//                  string employeeDepartments[], int& employeeCount, int& vacancies);
// void fireEmployee(int employeeIds[], string employeeNames[], int employeeAges[],
//                  string employeeDepartments[], int& employeeCount, int& vacancies);
// void displayAllEmployees(const int employeeIds[], const string employeeNames[],
//                         const int employeeAges[], const string employeeDepartments[],
//                         int employeeCount);
// void searchEmployeeById(const int employeeIds[], const string employeeNames[],
//                        const int employeeAges[], const string employeeDepartments[],
//                        int employeeCount);
// bool isIdUnique(const int employeeIds[], int employeeCount, int id);
// int findEmployeeIndex(const int employeeIds[], int employeeCount, int id);
// void saveToFile(const int employeeIds[], const string employeeNames[],
//                const int employeeAges[], const string employeeDepartments[],
//                int employeeCount, int vacancies);
// bool loadFromFile(int employeeIds[], string employeeNames[], int employeeAges[],
//                  string employeeDepartments[], int& employeeCount, int& vacancies);
// void clearInputBuffer();
//
// int main() {
//     // Parallel arrays to store employee data
//     int employeeIds[MAX_EMPLOYEES];
//     string employeeNames[MAX_EMPLOYEES];
//     int employeeAges[MAX_EMPLOYEES];
//     string employeeDepartments[MAX_EMPLOYEES];
//
//     int employeeCount = 0;
//     int vacancies = 10; // Initial number of vacancies
//     int choice;
//
//     // Try to load existing data
//     if (loadFromFile(employeeIds, employeeNames, employeeAges, employeeDepartments, employeeCount, vacancies)) {
//         cout << "Employee data loaded successfully.\n";
//     } else {
//         cout << "No existing data found or error loading data. Starting with empty system.\n";
//     }
//
//     do {
//         displayMenu();
//         cout << "Enter your choice: ";
//
//         // Input validation for menu choice
//         while (!(cin >> choice) || choice < 0 || choice > 6) {
//             cout << "Invalid choice. Please enter a number between 0 and 6: ";
//             clearInputBuffer();
//         }
//
//         switch (choice) {
//             case 1:
//                 hireEmployee(employeeIds, employeeNames, employeeAges, employeeDepartments, employeeCount, vacancies);
//                 break;
//             case 2:
//                 fireEmployee(employeeIds, employeeNames, employeeAges, employeeDepartments, employeeCount, vacancies);
//                 break;
//             case 3:
//                 displayAllEmployees(employeeIds, employeeNames, employeeAges, employeeDepartments, employeeCount);
//                 break;
//             case 4:
//                 searchEmployeeById(employeeIds, employeeNames, employeeAges, employeeDepartments, employeeCount);
//                 break;
//             case 5:
//                 cout << "Current vacancies: " << vacancies << endl;
//                 break;
//             case 6:
//                 saveToFile(employeeIds, employeeNames, employeeAges, employeeDepartments, employeeCount, vacancies);
//                 break;
//             case 0:
//                 cout << "Exiting program. Saving data...\n";
//                 saveToFile(employeeIds, employeeNames, employeeAges, employeeDepartments, employeeCount, vacancies);
//                 cout << "Data saved. Goodbye!\n";
//                 break;
//             default:
//                 cout << "Invalid choice. Please try again.\n";
//         }
//
//         cout << "\nPress Enter to continue...";
//         clearInputBuffer();
//         cin.get();
//
//     } while (choice != 0);
//
//     return 0;
// }
//
// void displayMenu() {
//     cout << "\n===== HR MANAGEMENT SYSTEM =====\n";
//     cout << "1. Hire Employee\n";
//     cout << "2. Fire Employee\n";
//     cout << "3. Display All Employees\n";
//     cout << "4. Search Employee by ID\n";
//     cout << "5. Check Vacancies\n";
//     cout << "6. Save Data\n";
//     cout << "0. Exit\n";
//     cout << "================================\n";
// }
//
// void hireEmployee(int employeeIds[], string employeeNames[], int employeeAges[],
//                  string employeeDepartments[], int& employeeCount, int& vacancies) {
//     if (vacancies <= 0) {
//         cout << "Error: No vacancies available. Cannot hire new employees.\n";
//         return;
//     }
//
//     if (employeeCount >= MAX_EMPLOYEES) {
//         cout << "Error: Maximum employee limit reached.\n";
//         return;
//     }
//
//     int id;
//     string name;
//     int age;
//     string department;
//
//     cout << "\n--- Hire New Employee ---\n";
//
//     // Get and validate employee ID
//     cout << "Enter Employee ID: ";
//     while (!(cin >> id) || id <= 0) {
//         cout << "Invalid ID. Please enter a positive number: ";
//         clearInputBuffer();
//     }
//
//     // Check if ID is unique
//     if (!isIdUnique(employeeIds, employeeCount, id)) {
//         cout << "Error: Employee ID already exists. Please use a unique ID.\n";
//         return;
//     }
//
//     clearInputBuffer();
//
//     // Get employee name
//     cout << "Enter Employee Name: ";
//     getline(cin, name);
//
//     // Get and validate employee age
//     cout << "Enter Employee Age: ";
//     while (!(cin >> age) || age < 18 || age > 65) {
//         cout << "Invalid age. Please enter an age between 18 and 65: ";
//         clearInputBuffer();
//     }
//
//     clearInputBuffer();
//
//     // Get employee department
//     cout << "Enter Employee Department: ";
//     getline(cin, department);
//
//     // Add employee to arrays
//     employeeIds[employeeCount] = id;
//     employeeNames[employeeCount] = name;
//     employeeAges[employeeCount] = age;
//     employeeDepartments[employeeCount] = department;
//
//     employeeCount++;
//     vacancies--;
//
//     cout << "Employee hired successfully. Remaining vacancies: " << vacancies << endl;
// }
//
// void fireEmployee(int employeeIds[], string employeeNames[], int employeeAges[],
//                  string employeeDepartments[], int& employeeCount, int& vacancies) {
//     if (employeeCount == 0) {
//         cout << "Error: No employees to fire.\n";
//         return;
//     }
//
//     int id;
//     cout << "\n--- Fire Employee ---\n";
//     cout << "Enter Employee ID to fire: ";
//
//     while (!(cin >> id)) {
//         cout << "Invalid ID. Please enter a number: ";
//         clearInputBuffer();
//     }
//
//     int index = findEmployeeIndex(employeeIds, employeeCount, id);
//
//     if (index == -1) {
//         cout << "Error: Employee with ID " << id << " not found.\n";
//         return;
//     }
//
//     cout << "Are you sure you want to fire " << employeeNames[index] << "? (y/n): ";
//     clearInputBuffer();
//     char confirm;
//     cin >> confirm;
//
//     if (confirm == 'y' || confirm == 'Y') {
//         // Shift all elements after the removed employee
//         for (int i = index; i < employeeCount - 1; i++) {
//             employeeIds[i] = employeeIds[i + 1];
//             employeeNames[i] = employeeNames[i + 1];
//             employeeAges[i] = employeeAges[i + 1];
//             employeeDepartments[i] = employeeDepartments[i + 1];
//         }
//
//         employeeCount--;
//         vacancies++;
//
//         cout << "Employee fired successfully. Available vacancies: " << vacancies << endl;
//     } else {
//         cout << "Operation cancelled.\n";
//     }
// }
//
// void displayAllEmployees(const int employeeIds[], const string employeeNames[],
//                         const int employeeAges[], const string employeeDepartments[],
//                         int employeeCount) {
//     if (employeeCount == 0) {
//         cout << "No employees to display.\n";
//         return;
//     }
//
//     cout << "\n--- All Employees ---\n";
//     cout << "ID\tName\t\tAge\tDepartment\n";
//     cout << "----------------------------------------\n";
//
//     for (int i = 0; i < employeeCount; i++) {
//         cout << employeeIds[i] << "\t"
//              << employeeNames[i] << "\t\t"
//              << employeeAges[i] << "\t"
//              << employeeDepartments[i] << endl;
//     }
//
//     cout << "----------------------------------------\n";
//     cout << "Total Employees: " << employeeCount << endl;
// }
//
// void searchEmployeeById(const int employeeIds[], const string employeeNames[],
//                        const int employeeAges[], const string employeeDepartments[],
//                        int employeeCount) {
//     if (employeeCount == 0) {
//         cout << "No employees in the system.\n";
//         return;
//     }
//
//     int id;
//     cout << "\n--- Search Employee ---\n";
//     cout << "Enter Employee ID: ";
//
//     while (!(cin >> id)) {
//         cout << "Invalid ID. Please enter a number: ";
//         clearInputBuffer();
//     }
//
//     int index = findEmployeeIndex(employeeIds, employeeCount, id);
//
//     if (index == -1) {
//         cout << "Employee with ID " << id << " not found.\n";
//         return;
//     }
//
//     cout << "\n--- Employee Details ---\n";
//     cout << "ID: " << employeeIds[index] << endl;
//     cout << "Name: " << employeeNames[index] << endl;
//     cout << "Age: " << employeeAges[index] << endl;
//     cout << "Department: " << employeeDepartments[index] << endl;
// }
//
// bool isIdUnique(const int employeeIds[], int employeeCount, int id) {
//     for (int i = 0; i < employeeCount; i++) {
//         if (employeeIds[i] == id) {
//             return false;
//         }
//     }
//     return true;
// }
//
// int findEmployeeIndex(const int employeeIds[], int employeeCount, int id) {
//     for (int i = 0; i < employeeCount; i++) {
//         if (employeeIds[i] == id) {
//             return i;
//         }
//     }
//     return -1; // Not found
// }
//
// void saveToFile(const int employeeIds[], const string employeeNames[],
//                const int employeeAges[], const string employeeDepartments[],
//                int employeeCount, int vacancies) {
//     ofstream outFile(FILE_NAME);
//
//     if (!outFile) {
//         cout << "Error: Unable to open file for writing.\n";
//         return;
//     }
//
//     // First line: number of employees and vacancies
//     outFile << employeeCount << " " << vacancies << endl;
//
//     // Write each employee's data
//     for (int i = 0; i < employeeCount; i++) {
//         outFile << employeeIds[i] << endl;
//         outFile << employeeNames[i] << endl;
//         outFile << employeeAges[i] << endl;
//         outFile << employeeDepartments[i] << endl;
//     }
//
//     outFile.close();
//     cout << "Data saved successfully.\n";
// }
//
// bool loadFromFile(int employeeIds[], string employeeNames[], int employeeAges[],
//                  string employeeDepartments[], int& employeeCount, int& vacancies) {
//     ifstream inFile(FILE_NAME);
//
//     if (!inFile) {
//         return false; // File doesn't exist or can't be opened
//     }
//
//     // Read number of employees and vacancies
//     inFile >> employeeCount >> vacancies;
//     inFile.ignore(); // Ignore newline after reading numbers
//
//     // Read each employee's data
//     for (int i = 0; i < employeeCount; i++) {
//         inFile >> employeeIds[i];
//         inFile.ignore();
//
//         getline(inFile, employeeNames[i]);
//         inFile >> employeeAges[i];
//         inFile.ignore();
//
//         getline(inFile, employeeDepartments[i]);
//     }
//
//     inFile.close();
//     return true;
// }
//
// void clearInputBuffer() {
//     cin.clear();
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
// }