/*
COPYRIGHT (C) 2017 Devin Hopkins (41900350) All rights reserved.
CSI Assignment 3 A
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 07.09.2017
Purpose: This program is a rectangle printer that allows the user to enter the rectangle's dimensions
*/

#include <iostream>

int main()
{
    // Importing the standard functions
    using std::cout;
    using std::cin;
    using std::endl;

    // Declaring and instatiating variables
    int width, length;
    bool validWidth = true, validLength = true;

    // Getting the user's initial input on the size of the rectangle
    cout << "\nHow wide would you like your rectangle to be? Note: Your number must be between 1 and 75." << endl;
    cin >> width;
    cout << "\nHow long would you like your rectangle to be? Note: Your number must be between 1 and 75." << endl;
    cin >> length;

    // Validating to make sure the user's input is within the set parameters
    if (width <= 0 || width > 75)
    {
        validWidth = false;
    }
    if (length <= 0 || length > 75)
    {
        validLength = false;
    }

    // If the user's input was not in the correct range, this loop will make them correct it
    // They can't get out of this loop until they have entered numbers inside the set parameters
    while (!validWidth || !validLength)
    {
        if (!validWidth)
        {
            cout << "\nYou did not enter a valid width. Enter a number between 1 and 75." << endl;
            cin >> width;
        }
        if (!validLength)
        {
            cout << "\nYou did not enter a valid length. Enter a number between 1 and 75." << endl;
            cin >> length;
        }

        // Again, just making sure they entered valid numbers
        validWidth = true;
        validLength = true;
        if (width <= 0 || width > 75)
        {
            validWidth = false;
        }
        if (length <= 0 || length > 75)
        {
            validLength = false;
        }
    }

    // This is to make the spacing look nicer
    cout << endl;

    // Printing out the rectangle with the user's input of width and length
    for (int x = 0; x < length; x++)
    {
        for (int y = 0; y < width; y++)
        {
            cout << "X";
        }
    cout << endl;
    }

    // Again, this is just to make the output look nicer
    cout << endl;

    return 0;
}
