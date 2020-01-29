/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 9A
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 11.30.2017
Purpose: The purpose of this program is to learn how to use pointers to swap 2 c-strings.
*/


// Importing the necessary libraries
#include <iostream>
#include <cstring>

// Importing the necessary functions from the std library
using std::cout;
using std::endl;

// Function prototypes
void reversee(char str[]);

int main()
{
    // these are the test cases
    char str1[] = "time";
    char str2[] = "straw";
    char str3[] = "deliver";
    char str4[] = "star";
    char str5[] = "knits";

    cout << "The strings before reversing: " << endl;
    cout << str1 << " " << str2 << " " << str3 << " " << str4 << " " << str5 << " " << endl;

    reversee(str1);
    reversee(str2);
    reversee(str3);
    reversee(str4);
    reversee(str5);

    cout << "\nThe strings after reversing: " << endl;
    cout << str1 << " " << str2 << " " << str3 << " " << str4 << " " << str5 << " " << endl;

    return 0;
}

/*
    PRE: Expects a c-string
    POST: Reverses the order of the c-string
*/
void reversee(char str[])
{
    // Declaring and initializing necessary variables
    char *firstLetter = str;
    int len = strlen(str);
    char temp = ' ';

    // Going through the half the string, but swapping the entire string in the process
    for (int x = 0; x < len / 2; ++x)
    {
        // Swapping the first and last letter and then working towards the middle as x increases
        temp = *(firstLetter + x);
        *(firstLetter + x) = *(firstLetter + (len - x - 1));
        *(firstLetter + (len - x - 1)) = temp;
    }

    // Returning the pointer to null
    firstLetter = nullptr;
}
