/*
COPYRIGHT (C) 2017 Devin Hopkins (41900350) All rights reserved.
CSI Assignment Project Part 4
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 10.14.2017
Purpose: This program is a fitness tracker that helps note how many calories you burn and also details how
         intense your exercise was.
*/


// Importing all necessary libraries
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Importing all necessary std functions
using std::cin;
using std::cout;
using std::endl;
using std::string;


/*
    PRECONDITIONS: None

    POSTCONDITIONS: Returns an integer holding the workout choice can be returned
*/
int displayMenu();

/*
    PRECONDITIONS: Assumes an int containing the lower limit (inclusive) of the valid area is sent first, followed by an int
                   that contains the upper limit (inclusive) of the valid area is sent, followed by an int that holds
                   the user's selected activity, and finally a message to display in case their number fell outside the
                   valid range

    POSTCONDITIONS: Returns true if the selection is within the valid range, returns false otherwise
*/
bool validateInt(int lowerRange, int upperRange, int selection, string &);

/*
    PRECONDITIONS: None

    POSTCONDITIONS: Returns a float containing the user's weight in kilograms
*/
float getKgWeight();

/*
    PRECONDITIONS: Assumes the integer sent in contains the selected activity

    POSTCONDITIONS: Returns the number of minutes the user spent doing their activity
*/
int getMinutes(int selection);

/*
    PRECONDITIONS: Assumes the first integer containing the user's selected activity is sent, followed by the number
                   of minutes they spent doing the activity

    POSTCONDITIONS: Returns true if they are allowed to do their selected activity for the time that they wish,
                    returns false otherwise
*/
bool validateMinutes(int selection, int minutesExercise);

/*
    PRECONDITIONS: Assumes the integer sent contains the user's selected activity

    POSTCONDITIONS: Returns the name of the user's activity
*/
string getWorkoutName(int selection);

/*
    PRECONDITIONS: Assumes the first int is the number of minutes spent exercising, followed by an int that contains
                   the user's selected activity, followed by a float containing the number of calories the user burned

    POSTCONDITIONS: None
*/
void printCaloriesBurned(int minutesExercise, int workoutSelection, float caloriesBurned);

/*
    PRECONDITIONS: Assumes the first integer sent contains the user's selected activity, followed by an int containing
                   the number of minutes the user did their activity for, and followed by a float containing the
                   user's weight in kilograms

    POSTCONDITIONS: Returns the number of calories burned by the user
*/
float calculateCaloriesBurned(int workoutSelection, int minutesExercise, float kgWeight);

/*
    PRECONDITIONS: Assumes a float will be sent given the number of calories the user burned

    POSTCONDITIONS: None
*/
void printActivityIntensity(float caloriesBurned);

/*
    PRECONDITIONS: Assumes the programmer wants to give the user a time to look at something before moving on. Causes
                   the program to stop until the user hits enter

    POSTCONDITIONS: None
*/
void buffer();

int main()
{
    // Declaring and initializing variables
    int workoutSelection = 0, minutesExercise = 0;
    float userKgWeight = 0, caloriesBurned = 0;

    // Making sure cout is as set up as can be
    srand(time(0));
    cout << std::showpoint << std::fixed << std::setprecision(1);

    // Seeing what the user wants to do before entering into the loop that is the activity
    workoutSelection = displayMenu();

    while(workoutSelection != 5)
    {
        // Getting the user's weight in kilograms
        userKgWeight = getKgWeight();

        // Getting the number of minutes the user did their activity
        minutesExercise = getMinutes(workoutSelection);

        // Calculating the number of calories the user burned doing their activity
        caloriesBurned = calculateCaloriesBurned(workoutSelection, minutesExercise, userKgWeight);

        // Displaying all the information to the user
        printCaloriesBurned(minutesExercise, workoutSelection, caloriesBurned);
        printActivityIntensity(caloriesBurned);

        // This gives them time to look at the info before moving on (will move on after the user hits enter)
        buffer();

        // Sees what the user wants to do next
        workoutSelection = displayMenu();
    }

    // Tahnks them for visiting Devin's Fitness Center
    cout << "Thank you for visiting Devin's Fitness Center!" << endl;

    return 0;
}

/*
    PRECONDITIONS: None

    POSTCONDITIONS: Returns an integer holding the workout choice can be returned
*/
int displayMenu()
{
    // declaring and initializing variables
    int workoutSelection = 0;
    int userID = rand() % 100000;
    string errorMsg = "That is an invalid choice. Please choose a number between 1 and 5.";

    // Making a static variable to keep track of how many exercises are done today
    static int hitsToday = 0;
    hitsToday += 1;

    // This do while loop will keep displaying the menu and asking for the user's input until they give a valid input
    do
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

        // Makes the user ID and the number of activities done today appear nice and neat on the right with leading
        // zeros
        cout << std::setw(60) << "User ID: " << std::setfill('0') << std::setw(5) << std::right << userID << endl;
        cout << std::setw(60) << std::right << std::setfill(' ') << "Number of Hits Today: "
             << std::setw(5) << std::right << std::setfill('0') << hitsToday << endl;
        cout << std::setfill(' ');

        // Gets the user's input
        cout << "\nEnter the workout that you wish to track, or quit to exit: ";
        cin >> workoutSelection;
        cout << endl;

    // Validates the user's input, if invalid will go back to the beginning of the loop
    }while(!validateInt(1, 5, workoutSelection, errorMsg));

    // Return's the user's workout selection
    return workoutSelection;
}

/*
    PRECONDITIONS: Assumes an int containing the lower limit (inclusive) of the valid area is sent first, followed by an int
                   that contains the upper limit (inclusive) of the valid area is sent, followed by an int that holds
                   the user's selected activity, and finally a message to display in case their number fell outside the
                   valid range

    POSTCONDITIONS: Returns true if the selection is within the valid range, returns false otherwise
*/
bool validateInt(int lowerRange, int upperRange, int selection, string &msg)
{
   // Checks to see what they entered, and if they entered inside the requested range. If not, will clear cin, return
   // false, and display the given error message
   if (cin.fail() || selection < lowerRange || selection > upperRange)
   {
      // Clearing cin
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      // Displaying the given error message
      cout << msg << endl;

      // Returning false
      return false;
   }

   // If all good, returns true
   return true;
}

/*
    PRECONDITIONS: None

    POSTCONDITIONS: Returns a float containing the user's weight in kilograms
*/
float getKgWeight()
{
    // Declaring and initializing variables
    float poundWeight = 0;
    string errorMsg = "That was an invalid weight. Enter a number greater than 0.";

    // This loop will keep the user in until they enter a number greater than 0
    do
    {
        // Gets the user's input
        cout << "Enter your weight (in pounds): ";
        cin  >> poundWeight;
        cout << endl;

    // Validates the user's input. If invalid, will make them go back to the beginning of the loop
    }while(!validateInt(1, INT_MAX, poundWeight, errorMsg));

    // Converting the user's weight (input in pounds) to kilograms
    float kgWeight = poundWeight / 2.2;

    // Returning the user's weight in kilograms
    return kgWeight;
}

/*
    PRECONDITIONS: Assumes the integer sent in contains the selected activity

    POSTCONDITIONS: Returns the number of minutes the user spent doing their activity
*/
int getMinutes(int workoutSelection)
{
    // Declaring a variable
    int minutesExercise = 0;

    // This loop will get the user's input and make sure it's valid
    do
    {
        // Getting the user's input
        cout << "Enter the number of minutes you wish to partake in " << getWorkoutName(workoutSelection) << ": ";
        cin >> minutesExercise;
        cout << endl;

    // Validating the user's input. If invalid, makes the user go back to the start of the loop
    }while(!validateMinutes(workoutSelection, minutesExercise));

    // Returns the number of minutes the user did their activity for
    return minutesExercise;
}

/*
    PRECONDITIONS: Assumes the first integer containing the user's selected activity is sent, followed by the number
                   of minutes they spent doing the activity

    POSTCONDITIONS: Returns true if they are allowed to do their selected activity for the time that they wish,
                    returns false otherwise
*/
bool validateMinutes(int workoutSelection, int minutesExercise)
{
    // Declaring a variable
    string errorMsg = "";

    // This switch statement specializes in making sure whatever activity the user is doing, they're doing it for the
    // allowed amount of of time and returns true if they are, or false if they're not
    switch(workoutSelection)
    {
    case 1:
        // Makes sure the user is doing the stationary bike between 30 and 60 minutes
        errorMsg = "You must use the stationary bike for between 30 and 60 minutes.";
        return validateInt(30, 60, minutesExercise, errorMsg);
    case 2:
        // Makes sure the user is doing the treadmill between 30 and 60 minutes
        errorMsg = "You must use the treadmill for between 30 and 60 minutes.";
        return validateInt(30, 60, minutesExercise, errorMsg);
    case 3:
        // Makes sure the user is working between 15 and 30 minutes
        errorMsg = "You must workout for between 15 and 30 minutes.";
        return validateInt(15, 30, minutesExercise, errorMsg);
    default:
        // Makes sure the user is doing hatha yoga between 60 and 90 minutes
        errorMsg = "You must do hatha yoga for between 60 and 90 minutes.";
        return validateInt(60, 90, minutesExercise, errorMsg);
    }
}

/*
    PRECONDITIONS: Assumes the integer sent contains the user's selected activity

    POSTCONDITIONS: Returns the name of the user's activity
*/
string getWorkoutName(int workoutSelection)
{

    // This switch statement converts the user's int activity choice to the corresponding string activity choice and
    // returns the string
    switch(workoutSelection)
    {
    case 1:
        return "stationary bike";
    case 2:
        return "treadmill";
    case 3:
        return "workout";
    default:
        return "hatha yoga";
    }
}

/*
    PRECONDITIONS: Assumes the first int is the number of minutes spent exercising, followed by an int that contains
                   the user's selected activity, followed by a float containing the number of calories the user burned

    POSTCONDITIONS: None
*/
void printCaloriesBurned(int minutesExercise, int workoutSelection, float caloriesBurned)
{
    // Simply prints out all the info for the user to see
    cout << "Performing " << minutesExercise << " minutes of activity with the " << getWorkoutName(workoutSelection)
         << " burned " << caloriesBurned << " calories." << endl;
}

/*
    PRECONDITIONS: Assumes the first integer sent contains the user's selected activity, followed by an int containing
                   the number of minutes the user did their activity for, and followed by a float containing the
                   user's weight in kilograms

    POSTCONDITIONS: Returns the number of calories burned by the user
*/
float calculateCaloriesBurned(int workoutSelection, int minutesExercise, float kgWeight)
{
    // Declaring and initializing constants
    const float STATIONARY_BIKE_MET = 8.0;
    const float TREADMILL_MET = 10.0;
    const float WEIGHT_LIFTING_MET = 3.0;
    const float HATHA_YOGA_MET = 2.5;

    // This switch statement figures out how many calories the user burned based on the amount of time they spent
    // doing their activity and their weight
    switch(workoutSelection)
    {
        case 1:
            return (minutesExercise / 60.0 * STATIONARY_BIKE_MET * kgWeight);
        case 2:
            return (minutesExercise / 60.0 * TREADMILL_MET * kgWeight);
        case 3:
            return (minutesExercise / 60.0 * WEIGHT_LIFTING_MET * kgWeight);
        default:
            return (minutesExercise / 60.0 * HATHA_YOGA_MET * kgWeight);
    }
}

/*
    PRECONDITIONS: Assumes a float will be sent given the number of calories the user burned

    POSTCONDITIONS: None
*/
void printActivityIntensity(float caloriesBurned)
{
    // These if statements firgure out how intense the uer's activity was and tells the user by outputting it
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

/*
    PRECONDITIONS: Assumes the programmer wants to give the user a time to look at something before moving on. Causes
                   the program to stop until the user hits enter

    POSTCONDITIONS: None
*/
void buffer()
{
    // Simply telling the user they need to press enter to continue and filling their entry into nothing, so it's
    // not saved
    cout << "\nPress enter to continue...";
    cin.get();

    // Clearing cin so no harm is done by what the user may have entered
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
