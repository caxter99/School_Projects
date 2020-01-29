/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment ***ENTER ASSIGNMENT***
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 ***ENTER DATE WITH THE FORMAT .07.09.2017***
Purpose: This program ***FINISH***
*/

// Importing the necessary libraries and files
#include <iomanip>
#include <iostream>
#include "TaxConstants.hpp"
#include "TAX.HPP"

// Importing the necessary namespace functions and TAXCONSTANTS namespace
using std::cout;
using std::cin;
using std::endl;
using namespace TAXCONSTANTS;

// PRE: Expects a float to be tested, then the minimum the float can be (inclusive), then the maximum the float can be (inclusive),
//      and lastly takes a string which has the error message in case the float falls outside of the given range
// POST: Returns true if the tested float is within the range, false otherwise. Also, prints uot an error message if the tested float
//       falls outside the range
bool validFloat(float input, float minimum, float maximum, std::string error)
{
    using std::cout;
    using std::cin;
    using std::endl;
    // Checks to see if the float is in range or not. If not, it goes into this if statement
    if (cin.fail() || input < minimum || input > maximum)
    {
        // Prints out the error, resets cin, and returns false
        cout << error << endl;
        cin.clear();
        cin.ignore();
        return false;
    }

    // Returns true if the float is in range
    return true;
}

// PRE: Expects an array with taxPayer structs
// POST: Prints out the taxes each taxPayer owes
void taxPrint(taxPayer infoArray[])
{
    // Prints out the tax information for each of the taxPayer structs
    cout << std::setprecision(2) << std::fixed;
    cout << "Taxes due for this year:\n" << endl;
    for (int x = 0; x < SIZE; ++x)
    {
        cout << "Tax Payer # " << x + 1 << ": $ " << infoArray[x].taxes << endl;
    }
}

// PRE: Expects an array with taxPayer structs
// POST: Will have all the taxPayer structs filled by asking the user to input all the necessary stats
void taxTaker(taxPayer infoArray[])
{
    cout << "Please enter the annual income and tax rate for 2 tax payers:" << endl;
    for (int x = 0; x < SIZE; ++x)
    {
        // Gets the annual income of each taxPayer
        float income = 0.0;
        cout << "\nEnter this year's income for tax payer " << x + 1 << ": ";
        cin >> income;

        // Checks to see if the user's input is valid
        while(!validFloat(income, MIN_INCOME, MAX_INCOME, "\nInvalid input. Please enter a number greater than 0."))
        {
            cout << "Enter this year's income for tax payer " << x + 1 << ": ";
            cin >> income;
        }

        // Gets the tax rate each person pays
        float rate = 0.0;
        cout << "Enter the tax rate for tax payer # " << x + 1 << ": ";
        cin >> rate;

        // Checks to see if the user's value is valid
        while(!validFloat(rate, MIN_RATE, MAX_RATE, "\nInvalid input. Please enter a number between 0.1 and 9.9."))
        {
            cout << "Enter the tax rate for tax payer # " << x + 1 << ": ";
            cin >> rate;
        }

        // Puts the information given by the user into the struct
        infoArray[x].income = income;
        infoArray[x].taxRate = rate;
        infoArray[x].taxes = income * (rate / 100);
    }

    // Making sure the formatting stays nice
    cout << endl;
}
