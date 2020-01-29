/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 1A
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 1.25.2018
Purpose: The purpose of this program is to delete repeats with unnamed namespace, .cpp, and .hpp files
*/


// Importing all necessary files and libraries
#include <iostream>
#include <memory>
#include "noRepeats.hpp"


// Main
int main()
{
    // Importing necessary functions
    using std::unique_ptr;

    // Declaring and initializing all necessary variables
    char originalArray[SIZE];
    std::unique_ptr<char[]> noRepeatsArray;

    // Loading the array with lowercase letters to suit testing purposes
    originalArray[0] = 'a';
    originalArray[1] = 'b';
    originalArray[2] = 'b';
    originalArray[3] = 'c';
    originalArray[4] = 'a';
    originalArray[5] = 'c';
    originalArray[6] = 'a';
    originalArray[7] = 'c';
    originalArray[8] = 'b';
    originalArray[9] = 'c';

    // Getting rid of all the repeats
    noRepeatsArray = screwRepeats(originalArray);

    // Declaring a counter to see how many unique lowercase letters in the array
    int counter = 0;

    // going through the dynamic array of unique lowercase letters
    while (noRepeatsArray[counter] >= 97 && noRepeatsArray[counter] <= 122)
    {
        // Printing out each unique lowercase letter
        std::cout << noRepeatsArray[counter] << std::endl;

        // Increasing the counter
        ++counter;
    }

    // Telling the user how many unique lowercase letters there are
    std::cout << "\nThere were " << counter << " unique lowercase letters in the array." << std::endl;

    return 0;
}
