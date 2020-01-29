/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 6A
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 10.27.2017
Purpose: The purpose of this program is to organize the amount of sales and product each farm has from a file.
*/

// Importing all the necessary packages for the program
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

// Importing the functions from the standard library that we need for the program
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

/*
    PRE: This function expects an address to a file
    POST: A string is returned containing the name of a farm
*/
string getFarmName(ifstream &fin);

/*
    PRE: This function expects an address to a file
    POST: A string is returned containing the product that the farm produces
*/
string getProductName(ifstream &fin);

/*
    PRE: This function expects an address to a file
    POST: An integer is returned containing the amount of product the farm produces
*/
int getNumOfItems(ifstream &fin);

/*
    PRE: This function expects an address to a file
    POST: A double is returned containing the cost of one item from the farm
*/
double getCostPerItem(ifstream &fin);

/*
    PRE: None
    POST: None, this function simply displays the header for the farmer's market
*/
void displayHeader();

/*
    PRE: This function expects a string to be sent in containing a farm's name, then an int containing the total number of items the farm produces, and lastly
         a double containing the total cost of the all the items the farm produces
    POST: None, this function simply displays all the data in a nive orderly fashion
*/
void nicelyDisplayRecordings(string previousFarmName, int totalNumOfItems, double total);

int main()
{
    // Importing one last standard library function to use just in this scope
    std::ifstream fin;

    // Declaring and instantializing necessary variables
    int numOfItems = 0, totalNumOfItems = 0;
    string farmName = "", previousFarmName = "", productName = "";
    double costPerItem = 0, total = 0;

    // Opening the file
    fin.open("ASSGN6-B.txt");

    // Making sure the file was able to be reached, if it can, the if will be used, if it can't, the else will be used
    if(!fin.fail())
    {
        // Displaying the header
        displayHeader();

        // Getting the first farm name
        farmName = getFarmName(fin);

        while(!fin.eof())
        {
            // Getting all the information of the farm, including the name of the product, cost per item, and the number of items
            numOfItems = getNumOfItems(fin);
            productName = getProductName(fin);
            costPerItem = getCostPerItem(fin);

            // Calculating the total number of items and the total cost (in case the farm has multiple items)
            total += costPerItem * numOfItems;
            totalNumOfItems += numOfItems;

            // Getting the next farm name to see if it matches the previous farm name
            previousFarmName = farmName;
            farmName = getFarmName(fin);

            // If the two farm names don't match, then the information from the farm is displayed
            if (farmName != previousFarmName)
            {
                // Displaying the farm's information
                nicelyDisplayRecordings(previousFarmName, totalNumOfItems, total);

                // Resetting the total cost and the ttoal number of items
                total = 0;
                totalNumOfItems = 0;
            }
        }
    }
    else
    {
        // Telling the user the file couldn't be reached and the program wouldn't work without connecting to the file
        cout << "Failed to connect to the file. Please make sure the file is named 'ASSGN6-B'." << endl;
    }

    return 0;
}

/*
    PRE: This function expects an address to a file
    POST: A string is returned containing the name of a farm
*/
string getFarmName(ifstream &fin)
{
    // Declaring and instantializing necessary variables
    string farmName = "";
    char singleCharacterFromFile = 'a';

    // This loop will grab all the characters and put them into a string until it has removed all the characters that
    // make up the name of the farm
    do
    {
        fin.get(singleCharacterFromFile);
        if (singleCharacterFromFile != ',' && singleCharacterFromFile != '\n')
        {
            farmName += singleCharacterFromFile;
        }
    }while(singleCharacterFromFile != ',' && !fin.eof());

    // Returning the farm name
    return farmName;
}

/*
    PRE: This function expects an address to a file
    POST: A string is returned containing the product that the farm produces
*/
string getProductName(ifstream &fin)
{
    // Declaring and instantializing necessary variables
    string productName = "";
    char singleCharacterFromFile = 'a';

    // This loop will grab all the characters and put them into a string until it has removed all the chracters
    // that make up the name of the product
    do
    {
        fin.get(singleCharacterFromFile);
        if (singleCharacterFromFile != ' ')
        {
            productName += singleCharacterFromFile;
        }
    }while((singleCharacterFromFile != ' ' || productName == "") && !fin.eof());

    // Returning the product name
    return productName;
}

/*
    PRE: This function expects an address to a file
    POST: An integer is returned containing the amount of product the farm produces
*/
int getNumOfItems(ifstream &fin)
{
    //// Declaring and instantializing necessary variables
    int numOfItems = 0;

    // Getting the number of items that the farm produces
    fin >> numOfItems;

    // Returning the number of items that the produces
    return numOfItems;
}

/*
    PRE: This function expects an address to a file
    POST: A double is returned containing the cost of one item from the farm
*/
double getCostPerItem(ifstream &fin)
{
    // Declaring and instantializing necessary variables
    double costOfItem = 0;

    // Getting the cost of the product
    fin >> costOfItem;

    // Returning the cost of the product
    return costOfItem;
}

/*
    PRE: None
    POST: None, this function simply displays the header for the farmer's market
*/
void displayHeader()
{
    // Nicely printing out the farmer's market header
    cout << "=======================================================================" << endl;
    cout << "=                      FARMER'S MARKET INVENTORY                      =" << endl;
    cout << "=======================================================================" << endl;
}

/*
    PRE: This function expects a string to be sent in containing a farm's name, then an int containing the total number of items the farm produces, and lastly
         a double containing the total cost of the all the items the farm produces
    POST: None, this function simply displays all the data in a nive orderly fashion
*/
void nicelyDisplayRecordings(string previousFarmName, int totalNumOfItems, double total)
{
    // Nicely displaying the information about the farm and the cost of all the products
    cout << std::setw(25) << std::left << previousFarmName << totalNumOfItems << " items contributed totaling $"
                     << std::setprecision(2) << std::fixed << total << endl;
}
