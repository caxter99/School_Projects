/*
Program: ASSIGN1-A
Name: Devin Hopkins
Purpose: This program will compute the total sales tax on a $95 purchase.
Assume the state sales tax is 4 percent and the county sales tax is 2 percent
*/

#include <iostream>
#include <iomanip>

// Declaring constants
const float STATE_TAX = 0.04;
const float COUNTY_TAX = 0.02;

int main()
{
    // Not using namespace, so must import a few namespace functions
    using std::cout;
    using std::endl;

    // Figuring out the sales tax and county tax
    float purchase = 95.00;
    cout << "Assignment 1-A" << endl;
    cout << "The total tax is: $" << std::fixed << std::showpoint << std::setprecision(2)
         << ((purchase * STATE_TAX) + (purchase * COUNTY_TAX)) << endl;

    return 0;
}
