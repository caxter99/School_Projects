/*
COPYRIGHT (C) 2017 Devin Hopkins (4190250) All rights reserved.
CSI Assignment 4B
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 09.30.2017
Purpose: The purpose of this program is to determine who wants to be a millionare
*/

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::ios;

// This function returns new balance after one year with the given interest rate
double newBalance(double, double);

// This function returns the new balance after a given number of years with the given interest
double newBalance(double, double, int);

// This function computes how long it would take with the beginning balance and the given interest to become a millionare
int yearsNeeded(double, double, double);

int main()
{
    // Defining my variables
    double initialBalance, interestRate;

    // Making sure that anytime I print something out it shows two decimal places, always
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);

    // Getting the initial deposit
    cout << "Enter your initial deposit: ";
    cin >> initialBalance;

    // Making sure they entered in valid data
    do{
        if (cin.fail() || initialBalance <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid data entered. Try again." << endl;
            cout << "Enter your initial deposit: ";
            cin >> initialBalance;
        }
    }while(cin.fail() || initialBalance <= 0);

    // Getting the interest rate
    cout << "\nEnter your interest rate (Note: 0.05 = 5%): ";
    cin >> interestRate;

    // Making sure they entered valid data
    do{
        if (cin.fail() || interestRate <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid data entered. Try again." << endl;
            cout << "Enter your interest rate (Note: 0.05 = 5%): ";
            cin >> interestRate;
        }
    }while(cin.fail() || interestRate <= 0);

    // Outputting the results
    cout << "\nAfter one year of interest: " << newBalance(initialBalance, interestRate) << endl;
    cout << "After ten years of compounded interest: " << newBalance(initialBalance, interestRate, 10) << endl;
    cout << "Years it would take to reach $1,000,000: " << yearsNeeded(initialBalance, interestRate, 1000000) << endl;

    return 0;
}

// This function returns new balance after one year with the given interest rate
double newBalance(double initialBalance, double interestRate)
{
    return initialBalance += (initialBalance * interestRate);
}

// This function returns the new balance after a given number of years with the given interest
double newBalance(double initialBalance, double interestRate, int n)
{
    for (int x = 0; x < n; x++)
    {
        initialBalance += newBalance(initialBalance, interestRate);
    }
    return initialBalance;
}

// This function computes how long it would take with the beginning balance and the given interest to become a millionare
int yearsNeeded(double initialBalance, double interestRate, double goal)
{
    int years = 0;
    while (initialBalance < goal)
    {
        years += 1;
        initialBalance += newBalance(initialBalance, interestRate);
    }
    return years;
}
