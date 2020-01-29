/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI assignment 1 A
Author:  Devin Hopkins
         djh155@zips.uakron.edu
Version. 1.01 07.09.2017
Purpose: This program will compute the number of calories the user will burn doing an excersize for a given time
*/

#include <iostream>
#include <iomanip>

int main()
{
    // Importing the standard
    using std::cout;
    using std::cin;
    using std::endl;
    using std::setprecision;
    using std::fixed;
    using std::right;
    using std::setw;

    // Declaring and instantiating variables
    const float STATIONARY_BIKE_MET = 8.0;
    const float TREADMILL_MET = 10.0;
    const float WEIGHT_LIFTING_MET = 3.0;
    const float HATHA_YOGA_MET = 2.5;
    int weight, minutes;
    double kgWeight, calories;

    // Printing out the logo
    cout << "__________________________________________________" << "\n|                                                |" << "\n|       Welcome to Devin's Fitness Center        | ";
    cout << "\n|                                                |" << "\n|________________________________________________|" << endl;

    // Getting the user's information
    cout << "\nEnter your weight: ";
    cin >> weight;
    cout << "Enter the number of minutes: ";
    cin >> minutes;
    cin.ignore();

    // Converting their weight from pounds to kilograms
    kgWeight = weight / 2.2;

    // Calculating and printing out the amount of calories they burned
    cout << "\n" << setw(70) << right << fixed << "Your total calories for riding the stationary bike was: " << setprecision(1) << minutes / 60.0 * STATIONARY_BIKE_MET * kgWeight << endl;
    cout << setw(70) << right << fixed << "Your total calories for running on the treadmill was: " << minutes / 60.0 * TREADMILL_MET * kgWeight << endl;
    cout << setw(70) << right << fixed << "Your total calories for weight lifting was: " << minutes / 60.0 * WEIGHT_LIFTING_MET * kgWeight << endl;
    cout << setw(70) << right << fixed << "Your total calories for doing Hatha yoga was: " << minutes / 60.0 * HATHA_YOGA_MET * kgWeight << "\n" << endl;

    return 0;
}
