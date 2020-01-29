// This is the Employee.cpp file for Project 2
// Devin Hopkins
// 4190350

// TESTING ONLY
// DO NOT CHANGE THIS FILE!!!!!

#include "Employee.h"

Employee::Employee(int i, std::string n, int pay)
{
    identifier = i;
    lastname = n;
    salary = pay;
}

void Employee::print(std::ostream &out = std::cout)
{
    out << identifier << " " << lastname << " " << salary << ": ";
}