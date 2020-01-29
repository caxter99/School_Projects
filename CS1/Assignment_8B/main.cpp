/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 8B
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 11.24.2017
Purpose: The purpose of this program is to crack the enemy's encryption.
*/

// Importing the necessary libraries
#include <iostream>
#include <fstream>

// Importing the most useful standard library functions
using std::cout;
using std::cin;
using std::endl;
using std::string;

// Global variable for the length of the char array
int LENGTH_OF_CHAR_ARRAY = 16;

void printChar(char message[]);
void decodeMessage(char message[], int key);
void copyCharArray(char keepTheSame[], char change[]);

int main()
{
    // Declaring and initializing the variables we need for the program
    char original[] = ":mmZ\\dxZmx]Zpgy";
    char copyOfOriginal[] = ":mmZ\\dxZmx]Zpgy";

    // Printing out the original message
    cout << "Original Encoded Message: ";
    printChar(original);
    cout << endl;

    // The key is a number from 1 to 100, and this loop will quickly go through each possibility
    for (int key = 1; key <= 100; ++key)
    {
        // This function decodes the message using the sent key
        decodeMessage(copyOfOriginal, key);

        // Printing out the message found from using the decrypting function
        cout << "Decoded Message (Key #" << key << "): ";
        printChar(copyOfOriginal);

        // Putting the original char array back into the one that will be decoded
        copyCharArray(original, copyOfOriginal);

        // Making sure the output stays looking nice and isn't too crowded
        cout << endl;
    }
}

/*
    PRE: Expects a char array
    POST: Nothing, but a the char array sent into the function will be printed out
*/
void printChar(char message[])
{
    // Going through each element in the char array individually
    for (int x = 0; x < LENGTH_OF_CHAR_ARRAY; ++x)
    {
        // Printing out one element at a time
        cout << message[x];
    }
    // Making the output stay nice
    cout << endl;
}

/*
    PRE: Expects a char array and an integer that contains a number 1 through 100
    POST: The function will have changed the char array sent in by using the decoding mechanism and the key
*/
void decodeMessage(char message[], int key)
{
    // Going through each element one at a time
    for (int x = 0; x < LENGTH_OF_CHAR_ARRAY; ++x)
    {
        // This is the enemy's decyption mechanism, changeseach char to a different char based on the original char's ASCII value
        if (message[x] + key > 126)
        {
            message[x] = char(32 + ((message[x] + key) - 127));
        }
        else
        {
            message[x] = char(message[x] + key);
        }
    }
}

/*
    PRE: Expects a char array (the one that will be kept the same and put into the other char array) and another char array (the one that
         will be replaced with the first char array sent in)
    POST: Both char arrays will contain what the first array had in it
*/
void copyCharArray(char keepTheSame[], char change[])
{
    // Going through each element in the first char array, one at a time and placing it in the second char array
    for (int x = 0; x < LENGTH_OF_CHAR_ARRAY; ++x)
    {
        change[x] = keepTheSame[x];
    }
}
