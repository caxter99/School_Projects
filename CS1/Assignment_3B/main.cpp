/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 3B
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 07.09.2017
Purpose: The purpose of this program is to create a game of Madlibs
*/

#include <iostream>

int main()
{
    // Importing necessary std functions
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    // Declaring variables
    string name = " ", noun = " ", bodyPart = " ", verb = " ";
    int number = 0;

    // Letting the user know what's going on
    cout << "\nWelcome to a game of Madlibs!\nFor this game, please answer all questions with the appropriate response.\nAt the end, a humorous story will be read to you. Enjoy!" << endl;

    // Beginning to get data from the user for the Madlibs response
    cout << "\nPlease enter a proper first name: ";
    cin >> name;
    cout << "\nPlease enter a plural noun: ";
    cin >> noun;
    cout << "\nPlease enter a body part (or some part of anatomy): ";
    cin >> bodyPart;
    cout << "\nPlease enter a verb: ";
    cin >> verb;
    cin.ignore();
    cout << "\nPlease enter an arbitrary number: ";
    cin >> number;

    // Giving them their story
    cout << "\nHere's your story!" << endl;
    cout << "The famous explorer " << name << " had nearly given up a life-long quest to find the Lost City of " << noun << " when one day the " << noun << " found the explorer." << endl;
    cout << "\nSurrounded by " << number << " " << noun << ", a tear came to " << name << "'s " << bodyPart << ". After all this time, the quest was finally over. And then, the " << noun << " promptly devoured " << name << "." << endl;
    cout << "\nThe moral of the story? Be careful what you " << verb << " for." << endl;

    return 0;
}
