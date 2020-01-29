/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 6B
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 10.26.2017
Purpose: The purpose of this program is read in a file 24 lines at a time so the user can read what the file contains.
*/

// Importing the necessary libraries for the program
#include <iostream>
#include <fstream>

// Importing the necessary functions for the program from the standard library without importing the entire library
using std::cout;
using std::cin;
using std::endl;

/*
    PRE: Expects an integer to be sent in
    POST: The user will be asked to hit enter, otherwise the program will halt. Also, the integer sent into the function will be set to 0
*/
void bufferCounterReset(int &ctr);

int main()
{
    // Importing necessary functions for the main() from the standard library
    using std::ifstream;
    using std::string;

    // Declaring and initializing variables and objects
    ifstream fin;
    string nameOfFile = "";

    // Getting the name of the file the user wishes to open
    cout << "What is the name of the file you wish to open? (The suffix '.txt' will be added for you)" << endl;
    getline(cin, nameOfFile);

    // Due to the nature of the compiler needing the suffix ".txt" and the user not being required to enter it, it is done
    // automatically here
    nameOfFile = nameOfFile + ".txt";

    // Attempting to open the file the user requested
    fin.open(nameOfFile.c_str());

    // Checking to see if the file the user entered was accessible or not. If not, it will go into the if branch
    if (fin.fail())
    {
        cout << endl << "The file entered does not exist. File name entered: " << nameOfFile << endl;
    }

    // However, if the file was able to be accessed, then the program goes into the else branch
    else
    {
        // This is just making the output look a little nicer
        cout << endl;

        // Declaring and initializing more necessary variables for this branch
        string lineFromFile = "";
        int ctr = 0;

        // Getting the first line of the file
        getline(fin, lineFromFile);

        // Entering into a loop that will make sure the entire file is printed, line by line
        while(!fin.eof())
        {
            // Printing out the line from the file, along with the line number (1 - 24)
            cout << ++ctr << ". " << lineFromFile << endl;

            // If 24 lines of code are printed, then the program will enter into this if statement
            if (ctr % 24 == 0)
            {
                // This function will reset the counter (ctr) and wait for the user to press the enter button before moving on
                bufferCounterReset(ctr);
            }

            // Getting the next line from the file
            getline(fin, lineFromFile);
        }
    }

    return 0;
}

/*
    PRE: Expects an integer to be sent in
    POST: The user will be asked to hit enter, otherwise the program will halt. Also, the integer sent into the function will be set to 0
*/
void bufferCounterReset(int &ctr)
{
    // Letting the user know they have to hit enter for the program to continue
    cout << "Press enter to continue..." << endl;
    cin.get();
    cout << endl;

    // Resetting the integer sent in to zero
    ctr = 0;
}
