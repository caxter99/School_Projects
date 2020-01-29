/*
COPYRIGHT (C) 2017 Devin Hopkins (41900350) All rights reserved.
CSI Assignment Project Part 2
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 07.09.2017
Purpose: This program is a fitness tracker that helps note how many calories you burn and also details how intense your excersize was
*/

#include <iostream>
#include <iomanip>

int main()
{
    // Importing the standard functions
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
    float kgWeight, calories;

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

    // Calculating and printing out the amount of calories they burned for biking
    cout << "\n" << setw(70) << right << fixed << "Your total calories for riding the stationary bike was: " << setprecision(1) << minutes / 60.0 * STATIONARY_BIKE_MET * kgWeight << endl;
    if (minutes / 60.0 * STATIONARY_BIKE_MET * kgWeight <= 200)
    {
        cout << "Light-intensity aerobic activity" << endl;
    }
    else if (minutes / 60.0 * STATIONARY_BIKE_MET * kgWeight <= 500)
    {
        cout << "Moderate-intensity activity" << endl;
    }
    else
    {
        cout << "Vigorous-intensity aerobic activity" << endl;
    }

    // Calculating and printing out the amount of calories they burned for running on the treadmill
    cout << setw(70) << right << fixed << "Your total calories for running on the treadmill was: " << minutes / 60.0 * TREADMILL_MET * kgWeight << endl;
    if (minutes / 60.0 * TREADMILL_MET * kgWeight <= 200)
    {
        cout << "Light-intensity aerobic activity" << endl;
    }
    else if (minutes / 60.0 * TREADMILL_MET * kgWeight <= 500)
    {
        cout << "Moderate-intensity activity" << endl;
    }
    else
    {
        cout << "Vigorous-intensity aerobic activity" << endl;
    }

    // Calculating and printing out the amount of calories they burned for weight lifting
    cout << setw(70) << right << fixed << "Your total calories for weight lifting was: " << minutes / 60.0 * WEIGHT_LIFTING_MET * kgWeight << endl;
    if (minutes / 60.0 * WEIGHT_LIFTING_MET * kgWeight <= 200)
    {
        cout << "Light-intensity aerobic activity" << endl;
    }
    else if (minutes / 60.0 * WEIGHT_LIFTING_MET * kgWeight <= 500)
    {
        cout << "Moderate-intensity activity" << endl;
    }
    else
    {
        cout << "Vigorous-intensity aerobic activity" << endl;
    }

    // Calculating and printing out the amount of calories they burned for doing hatha yoga
    cout << setw(70) << right << fixed << "Your total calories for doing Hatha yoga was: " << minutes / 60.0 * HATHA_YOGA_MET * kgWeight << endl;
    if (minutes / 60.0 * HATHA_YOGA_MET * kgWeight <= 200)
    {
        cout << "Light-intensity aerobic activity" << endl;
    }
    else if (minutes / 60.0 * HATHA_YOGA_MET * kgWeight <= 500)
    {
        cout << "Moderate-intensity activity" << endl;
    }
    else
    {
        cout << "Vigorous-intensity aerobic activity" << endl;
    }
    cout << endl;

    return 0;
}
