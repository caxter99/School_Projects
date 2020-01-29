/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 8A
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 11.16.2017
Purpose: The purpose of this program is to convert a file in English to Pig Latin.
*/

// Importing the necessary libraries
#include <iostream>
#include <fstream>

// Importing the most useful standard library functions
using std::cout;
using std::cin;
using std::endl;
using std::string;

/*
    PRE: Expects a string containing a word (or sentence)
    POST: Returns the same word (or sentence) as was sent, but in Pig Latin instead of the original language
*/
string convertToPigLatin(string wordInEnglish);

int main()
{
    // Importing the necessary function and objects for main
    using std::ifstream;

    // Creating the file object that will read data into the program
    ifstream inFile;

    // Attempting to open the file
    inFile.open("ASSGN_8A.txt");

    // If opening the file was a success, the code will enter into this if statement
    if (inFile)
    {
        // Creating necessary variables for this if statement
        string englishWord = "";
        string pigLatinWord = "";

        // This while loop will gather all the sentences/words from the file, convert to Pig Latin, and display both
        // version onto the output screen
        while(!inFile.eof())
        {
            // Getting a line from the file
            getline(inFile, englishWord);

            // Converting the sentence to Pig Latin
            pigLatinWord = convertToPigLatin(englishWord);

            // Outputting the results of the transformation along with the original
            cout << "  English: " << englishWord << endl;
            cout << "Pig Latin: " << pigLatinWord << endl;
            cout << endl;
        }
    }

    // If the program couldn't find the file, the code will enter into this else statement
    else
    {
        // Letting the user know the file couldn't be found
        cout << "The file could not be found." << endl;
    }

    // Closing the file nicely
    inFile.close();
}

/*
    PRE: Expects a string containing a word (or sentence)
    POST: Returns the same word (or sentence) as was sent, but in Pig Latin instead of the original language
*/
string convertToPigLatin(string wordInEnglish)
{
    // Creating the necessary variables for this function
    string wordInPigLatin = "";
    int y = wordInEnglish.find(" ");

    // If the sentence sent in is only one word, then the code will enter into this if statement
    if (y == -1)
    {
        wordInPigLatin = wordInEnglish.substr(1) + wordInEnglish.substr(0, 1) + "AY";
    }

    // If the sentence sent in is more than one word, then the code will enter into this else statement
    else
    {
        // While the sentence still has spaces, the code will go through this loop and convert each word into Pig Latin
        while (y != -1)
        {
            // Making each word into Pig Latin
            wordInPigLatin += (wordInEnglish.substr(1, y - 1) + wordInEnglish.substr(0, 1) + "AY ");

            // Getting rid of the words that are already translated to Pig Latin
            wordInEnglish = wordInEnglish.substr(y + 1);

            // Finding the next space in the sentence
            y = wordInEnglish.find(" ");
        }

        // After the sentence runs out of spaces, there is still one more word to convert. This line converts it
        wordInPigLatin += (wordInEnglish.substr(1, y - 1) + wordInEnglish.substr(0, 1) + "AY");
    }

    // Returning the sentence sent in, but in Pig Latin
    return wordInPigLatin;
}
