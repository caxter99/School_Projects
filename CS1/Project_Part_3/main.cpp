/*
COPYRIGHT (C) 2017 Devin Hopkins (41900350) All rights reserved.
CSI Assignment Project Part 3
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 09.30.2017
Purpose: This program is a fitness tracker that helps note how many calories you burn and also details how intense your excersize was
*/

// Importing necessary libraries
#include <iomanip>
#include <iostream>

// Importing necessary std functions
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ios;

// This function will display how intense a workout was based on the number of calories burned
void displayIntensity(float);

// This function calculates the number of calories burned based on which exercise the user did
float calculateCalories(int, int, float);

// This function gets the name of the workout based on teh number the user entered from the menu
string getWorkoutName(int);

// This function returns the number of minutes the guest is allowed to perform each workout
string getValidMinutes(int);

// This function checks to make sure the user is within the valid minutes of their activity
bool validMinutes(int, int);

// This function displays the menu
void displayMenu();

int main()
{
    // Declaring my variables
    int workoutSelection, weight, minutes;
    float kgWeight, caloriesBurned;

    // Making sure anytime I output a float/double it always displays one decimal place
    cout.precision(1);
    cout.setf(ios::fixed, ios::floatfield);

    // Asking the user what workout they wish to do
    displayMenu();
    cout << "\nEnter the workout that you wish to track, or quit to exit: ";
    cin >> workoutSelection;

    // Validating their entry
    do{
        if (cin.fail() || workoutSelection > 5 || workoutSelection < 1)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << endl;
            displayMenu();
            cout << "\nThat was an invalid option. Try again." << endl;
            cout << "Enter the workout that you wish to track, or quit to exit: ";
            cin >> workoutSelection;
        }
    }while(cin.fail() || workoutSelection > 5 || workoutSelection < 1);

    // Getting the user's weight in pounds
    cout << "\nEnter your weight in pounds: ";
    cin >> weight;

    // Validating the user's data
    do{
        if (cin.fail() || weight <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nThat was an invalid answer. Try again." << endl;
            cout << "Enter your weight in pounds: ";
            cin >> weight;
        }
    }while(cin.fail() || weight <= 0);

    // converting the user's weight from pounds to kilograms
    kgWeight = weight / 2.2;

    // Asking the user how long they intend to do their exercise
    cout << "\nEnter the number of minutes: ";
    cin >> minutes;

    // Validating the user's data
    do{
        if (cin.fail() || (!validMinutes(minutes, workoutSelection)))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nThat was an invalid answer (enter between " << getValidMinutes(workoutSelection) << " minutes)." << endl;
            cout << "Enter the number of minutes: ";
            cin >> minutes;
        }
    }while(cin.fail() || (!validMinutes(minutes, workoutSelection)));


    // Calculating how many calories the user burned while doing their exercise
    caloriesBurned = calculateCalories(workoutSelection, minutes, kgWeight);

    // Displaying the results and intensity
    cout << "\nYour total calories for " << getWorkoutName(workoutSelection) << " was: " << caloriesBurned << endl;
    displayIntensity(caloriesBurned);

    return 0;
}

// This function will display how intense a workout was based on the number of calories burned
void displayIntensity(float caloriesBurned)
{
    if (caloriesBurned > 500)
    {
        cout << "Vigorous-intensity aerobic activity" << endl;
    }
    else if (caloriesBurned > 200)
    {
        cout << "Moderate-intensity activity" << endl;
    }
    else
    {
        cout << "Light-intensity aerobic activity" << endl;
    }
}

// This function calculates the number of calories burned based on which exercise the user did
float calculateCalories(int workoutSelection, int minutes, float kgWeight)
{
    const float STATIONARY_BIKE_MET = 8.0;
    const float TREADMILL_MET = 10.0;
    const float WEIGHT_LIFTING_MET = 3.0;
    const float HATHA_YOGA_MET = 2.5;

    float caloriesBurned = -1.0;

    switch(workoutSelection)
    {
        case 1:
            caloriesBurned = minutes / 60.0 * STATIONARY_BIKE_MET * kgWeight;
            break;
        case 2:
            caloriesBurned = minutes / 60.0 * TREADMILL_MET * kgWeight;
            break;
        case 3:
            caloriesBurned = minutes / 60.0 * WEIGHT_LIFTING_MET * kgWeight;
            break;
        default:
            caloriesBurned = minutes / 60.0 * HATHA_YOGA_MET * kgWeight;
    }
    return caloriesBurned;
}

// This function gets the name of the workout based on teh number the user entered from the menu
string getWorkoutName(int workoutSelection)
{
    switch(workoutSelection)
    {
        case 1:
            return "stationary bike";
        case 2:
            return "treadmill";
        case 3:
            return "weight lifting";
        default:
            return "hatha yoga";
    }
    return "Error";
}

// This function returns the number of minutes the guest is allowed to perform each workout
string getValidMinutes(int workoutSelection)
{
    switch(workoutSelection)
    {
        case 1:
            return "30 and 60";
        case 2:
            return "30 and 60";
        case 3:
            return "15 and 30";
        default:
            return "60 and 90";
    }
    return "Error";
}

// This function checks to make sure the user is within the valid minutes of their activity
bool validMinutes(int minutes, int workoutSelection)
{
    switch(workoutSelection)
    {
        case 1:
            if (minutes > 60 || minutes < 30)
            {
                return false;
            }
            break;
        case 2:
            if (minutes > 60 || minutes < 30)
            {
                return false;
            }
            break;
        case 3:
            if (minutes > 30 || minutes < 15)
            {
                return false;
            }
            break;
        default:
            if (minutes > 90 || minutes < 60)
            {
                return false;
            }
    }
    return true;
}

// This function displays the menu
void displayMenu()
{
    cout << "__________________________________________________________________" << endl;
    cout << "|----------------------------------------------------------------|" << endl;
    cout << "|                     Devin's Fitness Center                     |" << endl;
    cout << "|                         Activity System                        |" << endl;
    cout << "|________________________________________________________________|" << endl;
    cout << "|                            MAIN MENU                           |" << endl;
    cout << "|                        1) Stationary Bike                      |" << endl;
    cout << "|                        2) Treadmill                            |" << endl;
    cout << "|                        3) Weight Lifting                       |" << endl;
    cout << "|                        4) Hatha Yoga                           |" << endl;
    cout << "|                        5) Quit                                 |" << endl;
    cout << "|________________________________________________________________|" << endl;
}
