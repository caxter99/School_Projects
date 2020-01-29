/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 7B
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 11.2.2017
Purpose: The purpose of this program is to find out the number of loads of each item was delivered to the farmer's market.
*/

// Importing necessary libraries
#include <iostream>
#include <iomanip>
#include <fstream>

// Importing necessary standard functions
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

/*
    PRE: Expects an array size 28 that can hold floats first, then an array size 28 that can hold strings, then an array size 28 that can
        hold ints, and finally an ifstream stream object that has been properly linked with a file
    POST: All the arrays will have their appropriate information sotred inside of them
*/
void putProductsInArrays(float (&pricesForProducts)[28], string (&namesForProducts)[28], int (&numberOfItems)[28], ifstream& inFile);

/*
    PRE: Expects an array size 28 that can hold floats first, then an array size 28 that can hold strings, then an array size 28 that can
        hold ints
    POST: Puts the nameForProducts array in alphabetical order, while moving all the array's elements around to match the nameForProducts
        array
*/
void bubbleSort(float (&pricesForProducts)[28], string (&namesForProducts)[28], int (&numberOfItems)[28]);

/*
    PRE: Expects an array size 28 that contains at least 2 strings, then an int variable that can be changed, and finally a string
        containing the name of an item
    POST: Finds and sees if the array already has an element with the name of the string sent in, if so, returns true and modifies the
        int variable to match the location of the repeated element, otherwise returns false and the placement variable is unmodified
*/
bool checkForRepeatedProduct(string (&namesForProducts)[28], int& placement, string nameOfItem);

/*
    PRE: Expects an array size 28 that can hold floats first, then an array size 28 that can hold strings, then an array size 28 that can
        hold ints
    POST: Puts the nameForProducts array in alphabetical order, while moving all the array's elements around to match the nameForProducts
        array
*/
void sortArraysInAlphabeticalOrder(float (&pricesForProducts)[28], string (&namesForProducts)[28], int (&numberOfItems)[28]);

/*
    PRE: Expects an array size 28 that contains strings and an int that contains the position that is going to be swapped
    POST: The array will have the position sent in and the position sent in plus one swapped
*/
void stringSwap(string (&namesForProducts)[28], int swapPos);

/*
    PRE: Expects an array size 28 that contains floats and an int that contains the position that is going to be swapped
    POST: The array will have the position sent in and the position sent in plus one swapped
*/
void floatSwap(float (&pricesForProducts)[28], int swapPos);

/*
    PRE: Expects an array size 28 that contains ints and an int that contains the position that is going to be swapped
    POST: The array will have the position sent in and the position sent in plus one swapped
*/
void intSwap(int (&numberOfItems)[28], int swapPos);

int main()
{
    // Initializing and declaring variables
    ifstream inFile;

    // Opening the file
    inFile.open("ASSGN6-B.txt");

    // Making sure the file opened successfully, if it didn't will go into the if statement
    if (inFile.fail())
    {
        // Letting the user know the file didn't open successully
        cout << "The file \"ASSGN6-B.txt\" could not be found." << endl;
    }

    // If the file did open successfully, the program will enter into this else
    else
    {
        // Declaring and initializing necessary variables and arrays
        float pricesForProducts [28];
        string namesForProducts [28];
        int numberOfItems [28];

        // Making sure the namesForProducts array isn't empty, as for some reason my code wouldn't work if the array was empty
        for (int x = 0; x < 28; ++x)
        {
            namesForProducts[x] = "zzz not empty";
        }

        // getting the information from the file and putting it into the arrays
        putProductsInArrays(pricesForProducts, namesForProducts, numberOfItems, inFile);

        // Putting the arrays in alphabetical order and making sure the rest of the arrays still correlate, all while using the bubble sort
        bubbleSort(pricesForProducts, namesForProducts, numberOfItems);

        // Setting up the cout for the output and declaring/initializing more variables
        int counter = 0, totalItems = 0;
        cout << std::setprecision(2) << std::fixed;

        // This loop displays all the necessary information for the user
        while(namesForProducts[counter] != "zzz not empty" && !(counter >= 28))
        {
            // Keeping track of the total number of items
            totalItems += numberOfItems[counter];

            // Printing out the information gathered for the user
            cout << std::setw(20) << std::left << namesForProducts[counter];
            cout << std::right << numberOfItems[counter] << " items totaling $";
            cout << pricesForProducts[counter] << endl;
            counter++;
        }
        // Letting the user know the total number of items at the farmer's market
        cout << "\nThere were " << totalItems << " items contributed to this week's event." << endl;
    }

    // Closing the file
    inFile.close();

    return 0;
}

/*
    PRE: Expects an array size 28 that can hold floats first, then an array size 28 that can hold strings, then an array size 28 that can
        hold ints, and finally an ifstream stream object that has been properly linked with a file
    POST: All the arrays will have their appropriate information sotred inside of them
*/
void putProductsInArrays(float (&pricesForProducts)[28], string (&namesForProducts)[28], int (&numberOfItems)[28], ifstream& inFile)
{
    // Declaring and initializing all the variables I will need for this function
    string lineFromFile = "", lineFromFile2 = "";
    int numberOfSingleItem = 0, counter = 0, placement = 0;
    float priceOfItem = 0.0;

    // This while loop will make sure I go through the entire file
    while (!inFile.eof())
    {
        // Collecting all the contents from my file and storing them into the necessary variables
        getline(inFile, lineFromFile, ',');
        inFile >> numberOfSingleItem;
        inFile >> lineFromFile;
        inFile >> priceOfItem;

        // This if statement checks to see if the product is already in the list, if it is, it will enter into the this if statement
        if (checkForRepeatedProduct(namesForProducts, placement, lineFromFile))
        {
            // This puts the inventory and additional cost with the original product and the original cost
            pricesForProducts[placement] = pricesForProducts[placement] + (priceOfItem * numberOfSingleItem);
            numberOfItems[placement] = numberOfItems[placement] + numberOfSingleItem;
        }

        // If this item is anew item, then the code will move into this else statement
        else
        {
            // This makes a new spot for a product and all the info that goes along with it
            pricesForProducts[counter] = priceOfItem * numberOfSingleItem;
            namesForProducts[counter] = lineFromFile;
            numberOfItems[counter] = numberOfSingleItem;

            // Making sure nothing is overwritten, so the counter variable is increased
            counter += 1;
        }

        // Making sure I get the rest of the line from the file
        getline(inFile, lineFromFile, '\n');
    }
}

/*
    PRE: Expects an array size 28 that contains at least 2 strings, then an int variable that can be changed, and finally a string
        containing the name of an item
    POST: Finds and sees if the array already has an element with the name of the string sent in, if so, returns true and modifies the
        int variable to match the location of the repeated element, otherwise returns false and the placement variable is unmodified
*/
bool checkForRepeatedProduct(string (&namesForProducts)[28], int& placement, string nameOfItem)
{
    for (int x = 0; x < 28; ++x)
    {
        if (namesForProducts[x] != "" && namesForProducts[x] == nameOfItem)
        {
            placement = x;
            return true;
        }
    }
    return false;
}

/*
    PRE: Expects an array size 28 that contains strings and an int that contains the position that is going to be swapped
    POST: The array will have the position sent in and the position sent in plus one swapped
*/
void stringSwap(string (&namesForProducts)[28], int swapPos)
{
    string stringPlaceHolder = namesForProducts[swapPos];
    namesForProducts[swapPos] = namesForProducts[swapPos + 1];
    namesForProducts[swapPos + 1] = stringPlaceHolder;
}

/*
    PRE: Expects an array size 28 that contains floats and an int that contains the position that is going to be swapped
    POST: The array will have the position sent in and the position sent in plus one swapped
*/
void floatSwap(float (&pricesForProducts)[28], int swapPos)
{
    float floatPlaceHolder = pricesForProducts[swapPos];
    pricesForProducts[swapPos] = pricesForProducts[swapPos + 1];
    pricesForProducts[swapPos + 1] = floatPlaceHolder;
}

/*
    PRE: Expects an array size 28 that contains ints and an int that contains the position that is going to be swapped
    POST: The array will have the position sent in and the position sent in plus one swapped
*/
void intSwap(int (&numberOfItems)[28], int swapPos)
{
    int intPlaceHolder = numberOfItems[swapPos];
    numberOfItems[swapPos] = numberOfItems[swapPos + 1];
    numberOfItems[swapPos + 1] = intPlaceHolder;
}

/*
    PRE: Expects an array size 28 that can hold floats first, then an array size 28 that can hold strings, then an array size 28 that can
        hold ints
    POST: Puts the nameForProducts array in alphabetical order, while moving all the array's elements around to match the nameForProducts
        array
*/
void bubbleSort(float (&pricesForProducts)[28], string (&namesForProducts)[28], int (&numberOfItems)[28])
{
    /// Making sure the loop runs enough times to get each and every element in place
    for (int x = 0; x < 28; x++)
    {
        // Making sure the inner loop, the one doing the swapping, runs enough times to find each element's home
        for (int y = 0; y < x - 1; y++)
        {
            // If the elements are out of order, they will enter into this if statement
            //if (namesForProducts[x + 1].compare(namesForProducts[x]) < 0)
            if (namesForProducts[y].compare(namesForProducts[y + 1]) > 0)
            {
                // Swapping the string array
                stringSwap(namesForProducts, y);

                // Swapping the int array
                intSwap(numberOfItems, y);

                // Swapping the float array
                floatSwap(pricesForProducts, y);
            }
        }
    }
}
