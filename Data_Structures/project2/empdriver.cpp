// This is the main.cpp file for Project 2
// Devin Hopkins
// 4190350

#include "empmaps.h"
#include "Employee.h"

int main(int argc, char const *argv[])
{
    // Gets the data and stores all of the employees in a vector
    vector<Employee> employeeVector = employees();

    // Creating a map of all the departments with the employees in them
    map<int, vector<Employee>> departmentMap = mapEmpDept(employeeVector);

    // Creating a map of the employees based on their salaries
    map<int, vector<Employee>> salaryMap = mapSalRange(employeeVector);

    // Printing the salary range of the employees (with the ordered employee map)
    printSalRange(salaryMap);

    // Giving a little bit of space in between the last print statement and the next time
    // something is going to printed
    cout << "\n";

    // Creating an unordered map of the employees with their departments
    unordered_map<int, vector<Employee>> unorderedDepartmentMap = umapEmpDept(employeeVector);

    // Creating an unordered map of the employees based on their salaries
    unordered_map<int,vector<Employee>> unorderedSalaryMap = umapSalRange(employeeVector);

    // Printing the salary range of the employees (with the unordered employee map)
    uprintSalRange(unorderedSalaryMap);

    return 0;
}