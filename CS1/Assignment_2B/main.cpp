/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 2B
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 07.09.2017
Purpose: This program is used to sum up all positive and negative integers
*/

#include <iostream>

int main()
{
    // Importing std functions
    using std::cout;
    using std::cin;
    using std::endl;

    // Declaring and initializing variables
    int num;
    int positiveSum = 0;
    int negativeSum = 0;
    int totalSum = 0;

    // Making sure the output isn't cluttered (I'm on a Mac)
    cout << endl;

    // Using a for loop so it's easy to get 10 numbers
    for (int x = 1; x <= 10; x++)
        {

            // The user is entering a number
            cout << "Enter a number: ";
            cin >> num;

            // Determining if the entered number is negative or positive and adding it to the correct sum as well as the total sum
            if (num >=0 )
            {
                positiveSum += num;
            }
            else
            {
                negativeSum += num;
            }
            totalSum += num;
    }

    // Outputing the results
    cout << "The sum of all of your integers is: " << totalSum << endl;
    cout << "The sum of all of your positive integers is: " << positiveSum << endl;
    cout << "The sum of all of your negative integers is: " << negativeSum << endl;

    return 0;
}
