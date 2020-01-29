/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 2A
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 07.09.2017
Purpose: This program is used to determine whether or not rooms are up to fire code
*/

#include <iostream>

int main()
{
    // Importing some std functions
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;

    // Declaring necessary variables
    const int LH312 = 42;
    const int CAS41 = 44;
    const int KH133 = 38;
    string goOn;
    int classChoice, attendence;

    // Entering a do while loop
    do{
        // Finding out what class they would like to check out
        cout << "\nWhat class would you like to check?\n1. Leigh Hall room 312\n2. College of Arts and Sciences room 41\n3. Kolbe Hall room 133" << endl;
        cin >> classChoice;

        // Making sure they entered a valid choice
        while (classChoice <= 0 || classChoice >= 4){
            cout << "\nThat is an invalid choice. Please choose again." << endl;
            cout << "What class would you like to check?\n1. Leigh Hall room 312\n2. College of Arts and Sciences room 41\n3. Kolbe Hall room 133" << endl;
            cin >> classChoice;
        }

        // Figuring out how many people are attending the class
        cout << "\nHow many people are attneding the class?" << endl;
        cin >> attendence;

        // Figuring out if the class in okay with fire code or not
        if (classChoice == 1){
            if (LH312 - attendence >= 0){
                cout << "The room is okay! It can hold " << LH312 - attendence << " more people." << endl;
            }
            else{
                cout << "There are too many people in the room. " << attendence - LH312 << " people need to leave for the class to be within fire code." << endl;
            }
        }
        if (classChoice == 2){
            if (CAS41 - attendence >= 0){
                cout << "The room is okay! It can hold " << CAS41 - attendence << " more people." << endl;
            }
            else{
                cout << "There are too many people in the room. " << attendence - CAS41 << " people need to leave for the class to be within fire code." << endl;
            }
        }
        if (classChoice == 3){
            if (KH133 - attendence >= 0){
                cout << "The room is okay! It can hold " << KH133 - attendence << " more people." << endl;
            }
            else{
                cout << "There are too many people in the room. " << attendence - KH133 << " people need to leave for the class to be within fire code." << endl;
            }
        }

        // Asking if the user wants to go again
        cin.ignore();
        cout << "\nWould you like to go again? (Enter Y or N): ";
        cin >> goOn;
        cin.ignore();
    }while(goOn == "Y" || goOn == "y");

    return 0;
}
