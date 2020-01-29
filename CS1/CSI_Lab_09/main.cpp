/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment CSI Lab 09
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 11.30.2017
Purpose: The purpose of this program is ***FINISH***
*/

/* Program id: CSLab09.cpp
 This is our template for CS Lab 09
 SEPARATE COMPILATION PRACTICE PROGRAM

 This program calculates the average number of days a company�s employees
are absent. The program should have the following functions:
� A function called by main that asks the user for the number of employees in
the company. This value should be returned as an int . (The function accepts no
arguments.)
� A function called by main that accepts one argument: the number of employees in
the company. The function should ask the user to enter the number of days each
employee missed during the past year. The total of these days should be returned as
an int .
� A function called by main that takes two arguments: the number of employees in
the company and the total number of days absent for all employees during the year.
The function should return, as a double , the average number of days absent. (This
function does not perform screen output and does not ask the user for input.)

We will take the functions out of this program and create separate compilation files
The names of the files should be:
getEmployees.hpp
getDaysOut.hpp
calcAverage.hpp
*/

#include <iostream>
#include <iomanip>
#include "calcAverage.h"
#include "getDaysOut.h"
#include "getEmployees.h"
// notice there is no namespace in this program

// Function prototypes
int getEmployees();
int getDaysOut(int &);
double calcAverage(int &, int &);

int main()
{
  // Get the number of employees.
  int employees = getEmployees();

  // Get the number of days missed by all employees.
  int daysOut = getDaysOut(employees);

  // Get the average number of days missed.
  double average = calcAverage(employees, daysOut);

  // Display the average.
  std::cout << "\nThe average number of days missed was "
            << std::fixed << std::setprecision(2) << average << ".\n\n";

  return 0;
}

