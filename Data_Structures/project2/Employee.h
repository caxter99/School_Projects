// This is the Employee.h file for Project 2
// Devin Hopkins
// 4190350

// TESTING ONLY
// DO NOT CHANGE THIS FILE!!!!!

#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED
#include <iostream>
#include <string>

class Employee{
public:
    Employee(int, std::string, int);
    int id() const {return identifier;}
    std::string name() const {return lastname;}
    int sal() const {return salary;}
    void print(std::ostream &);

private:
    int identifier;
    std::string lastname;
    int salary;
};

#endif // EMPLOYEE_H_INCLUDED