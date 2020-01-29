
// Importing all the necessary libraries
#include <iostream>
#include <memory>
#include <array>
#include "noRepeats.hpp"

namespace
{
    // Importing all necessary libraries and files
    #include <memory>

    // Declaring a constant for every file using this file
    const int SIZE = 10;
}

// Importing a necessary function

std::unique_ptr<char[]> deleteRepeats(char originalArray[])
{

    // Declaring all necessary variables
    //const int SIZE = 10;
    std::unique_ptr<char[]> uniqueCharacters(new char[SIZE]);

    // Setting the first element of uniqueCharacter to the first element of originalArray, since it has to be unique at this point
    uniqueCharacters[0] = originalArray[0];

    // Declaring another variable, which will be used to track the number of unique lowercase letters
    int counter = 1;

    // Going through and figuring out which elements are unique
    for (int x = 1; x < SIZE; ++x)
    {
        // This variable will determine if the element is unique or not, automatically assumed false unless proven otherwise
        bool isDuplicate = false;

        // This loop grabs all the characters from the uniqueCharacters array to compare them to the element in the originalArray
        for (int y = 0; y < counter; ++y)
        {
            // If the character is a duplicate, it will enter into this if statement
            if (uniqueCharacters[y] == originalArray[x])
            {
                isDuplicate = true;
                break;
            }
        }

        // If the character is not a duplicate, the code will enter into this if statement
        if (!isDuplicate)
        {
            // This will set the next element of uniqueCharacters to the unique character and move coutner up one
            uniqueCharacters[counter] = originalArray[x];
            ++counter;
        }
    }

    // Returning the dynamic array of unique characters
    return uniqueCharacters;
}
