/*
Program: Assignment 1B
Name: Devin Hopkins
Purpose: This program will ask the user to enter any number of quarters, dimes, and nickels and then output the amount
of money the change is equivalent to.
*/

#include <iostream>
#include <iomanip>

int main()
{
    // Importing namespace functions and declaring variables
    using std::cout;
    using std::cin;
    using std::endl;
    int quarters, dimes, nickels;
    float money;

    // Collecting data
    cout << "Enter number of quarters: ";
    cin >> quarters;
    cout << "Enter number of dimes: ";
    cin >> dimes;
    cout << "Enter number of nickels: ";
    cin >> nickels;

    // Computing the amount of money and displaying it
    money = (quarters * 0.25) + (dimes * 0.1) + (nickels * 0.05);
    cout << "The monetary value of your coins is $" << std::fixed << std::showpoint << std::setprecision(2) << money << endl;

    return 0;
}
