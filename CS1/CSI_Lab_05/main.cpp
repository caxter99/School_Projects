/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment Lab 05
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 10.19.2017
Purpose: The purpose of this program is to teach me refactoring and also to get the total cost of the user's purchase
*/

// Program id: CSLab05.cpp
// This is our template for CS Lab 05
// REFACTORING PRACTICE PROGRAM
// This program is used for the University of Akron, Department of Computer Science Laboratories
// Goal: refactor main into functions
// examine each portion in main and analyze the code for refactoring
// Next build your function prototype
// Next build your function by copying and pasting the code from main, into your function
// repeat until complete

#include<iostream>
#include <iomanip>

using namespace std; // forgive me for being lazy!

const double TAX_RATE = .05;

/*
    PRE: None
    POST: Returns a double = the price of the user's purchase, assumes a double variable will be waiting
*/
double getPrice();

/*
    PRE: None
    POST: Returns an int = the number of items the consumer purchased, assuming an int variable will be waiting
*/
int getQuantityPurchased();

/*
    PRE: None
    POST: Returns a char = what type of sale the user participated in, assumes a char variable will be waiting
*/
char getSaleType();

/*
    PRE: Assumes a double containing the price of the user's purchase will be sent, then an int with how many objects the user purchased for that price,
         and finally a char indicating what type of sale the user participated in
    POST: Returns a double = the total cost, assumes a double variable will be waiting
*/
double getTotal(double price, int number, char saleType);

/*
    PRE: Assumes a double containing the price of the user's purchase will be sent, then an int with how many objects the user purchased for that price,
         a double containing the total amount spent on the purchase, and finally a char indicating what type of sale the user participated in
    POST: None, just prints words out onto the command prompt
*/
void niceOutput(double price, int number, double total, char saleType);

int main()
{
   char saleType = 'a';
   int number = 0;
   double price = 0, total = 0; // Got rid of the double subTotal because it was no longer needed with the modifications made from refactoring

   /* This could become a function -
   cout << "Enter price $";
   cin >> price;*/
   price = getPrice();

   /*This could also become a function -
   cout << "Enter number purchased: ";
   cin >> number;*/
   number = getQuantityPurchased();

   /*This large chunk can also be done in a function -
   cout << "Type W if this is wholesale purchase. \n"
        << "Type R if this is retail purchase. \n"
        << "then press return... \n";
    cin.ignore();
    cin.get(saleType);*/
    saleType = getSaleType();

    /*This large if structure can also be put into a function. Doing this also gets rid of the variable subTotal from main -
    if ((saleType == 'W') || (saleType == 'w'))
    {
        total = price * number;
    }
    else if ((saleType == 'R') || (saleType == 'r'))
    {
        subTotal = price * number;
        total = subTotal + subTotal * TAX_RATE;
    }
    else
    {
        cout << "Error in the input...";
    }*/
    total = getTotal(price, number, saleType);


    /* Lastly, this nice output can be moved into a function -
    cout << setprecision(2) << fixed << showpoint << number << " items at $" << price << endl;
    cout << "Total bill $" << total;
    if ((saleType == 'R') || (saleType == 'r'))
    {
        cout << " includes sales tax.\n";
    }*/
    niceOutput(price, number, total, saleType);

    return 0;
}

/*
    PRE: None
    POST: Returns a double = the price of the user's purchase, assumes a double variable will be waiting
*/
double getPrice()
{
    double price = 0;
    cout << "Enter price $:";
    cin >> price;
    return price;
}

/*
    PRE: None
    POST: Returns an int = the number of items the consumer purchased, assuming an int variable will be waiting
*/
int getQuantityPurchased()
{
    int number = 0;
    cout << "Enter number purchased: ";
    cin >> number;
    return number;
}

/*
    PRE: None
    POST: Returns a char = what type of sale the user participated in, assumes a char variable will be waiting
*/
char getSaleType()
{
    char salesType = 'a';
    cout << "Type W if this is a wholesale purchase.\n"
         << "Type R if this is retail purchase. \n"
         << "then press return... \n";
    cin.ignore();
    cin.get(salesType);
    return salesType;
}

/*
    PRE: Assumes a double containing the price of the user's purchase will be sent, then an int with how many objects the user purchased for that price,
         and finally a char indicating what type of sale the user participated in
    POST: Returns a double = the total cost, assumes a double variable will be waiting
*/
double getTotal(double price, int number, char saleType)
{
    double total = 0;
    if ((saleType == 'W') || (saleType == 'w'))
    {
        total = price * number;
    }
    else if ((saleType == 'R') || (saleType == 'r'))
    {
        total = price * number + price * number * TAX_RATE;
    }
    else
    {
        cout << "Error in the input...";
    }
    return total;
}

/*
    PRE: Assumes a double containing the price of the user's purchase will be sent, then an int with how many objects the user purchased for that price,
         a double containing the total amount spent on the purchase, and finally a char indicating what type of sale the user participated in
    POST: None, just prints words out onto the command prompt
*/
void niceOutput(double price, int number, double total, char saleType)
{
    cout << setprecision(2) << fixed << showpoint << number << " items at $" << price << endl;
    cout << "Total bill $" << total;
    if ((saleType == 'R') || (saleType == 'r'))
    {
        cout << " includes sales tax.\n";
    }
}
