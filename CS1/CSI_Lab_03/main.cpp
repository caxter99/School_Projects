/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment CSI Lab 03
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 07.09.2017
Purpose: The purpose of this program is to create a game of Madlibs
*/

#include <iostream> // for input-output stream operations
#include <iomanip> // for providing parametric manipulators operations
#include <limits> // for providing elements with the characteristics of arithmetic types

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    double organisms = 0.0; // To hold the number of organisms

    //Get the starting number of organisms

    bool loopFlag = true; // Control flag for the loop

    do // post test loop
    {
        cout << "Enter the starting number of organisms: "; // output stream a message
        cin >> organisms; // input stream a message

        // Do not accept a number of less than 2 for the
        // starting size of the population
        if (cin.fail() || organisms < 2)
        {
            cout << "The starting number of organisms must be a valid number that is less than 2.\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            loopFlag = false; // change the boolean variable to end this loop (good input!)
        }
    }while(loopFlag);

    return 0; // ends the program and returns a zero back to the operating system
}

/*
Using std::... allows for the program to know what function we are referencing. This way, in case there's an update or a change in the namespace libray, our program won't have to change.

We use cin.fail() to check and see if they entered something other than a number. If they did, this will be true and they will have to reenter their data.

Short-circuit testing is used to determine of the user entered in an actual number (in this program). We use it because if the first condition is true,
there's no need to continue to check the second condition. This helps to speed up the program.

The parameters for the cin.ignore() tell the computer how far to ignore. In this case, it will ignore up to the '\n'. The numeric limits tell the computer how much
it's allowed to ignore. In this case, there's essentially no limit to how much the computer can ignore because we set it to max().
*/
