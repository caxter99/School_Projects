/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI assignment 1 A
Author:  Devin Hopkins
         djh155@zips.uakron.edu
Version. 1.01 07.09.2017
Purpose: This program will solve every problem and be the best one ever written ...
*/

#include <iostream>

using namespace std;

int main()
{
    // Constants
    const float STATE_TAX_RATE = .25;
    const float COUNTY_TAX_RATE = .75;
    const float FEDERAL_TAX_RATE = 1.25;

    // Variables
    int statePopulationTotal, countyPopulationTotal, federalPopulationTotal;

    // Starting the psuedo code
    // Declaring variables
    float priceAmount, newPriceAmount, priceDiscountAmount, stateTaxAmount, countyTaxAmount, totalAmount, charityAmount;
    int counter;

    // Setting the variables
    counter = 0;
    totalAmount = 0.00;
    charityAmount = 0.00;
    priceDiscountAmount = 0.00;
    stateTaxAmount = 0.00;
    countyTaxAmount = 0.00;

    // Manipulating the variables to find out the tax
    counter += 1;
    countyTaxAmount = priceAmount * 0.05;
    stateTaxAmount = priceAmount * 0.03;
    newPriceAmount = countyTaxAmount + stateTaxAmount + priceAmount;

    // Checking to see if there's any discounts or if any money goes to charity
    if (countyTaxAmount + stateTaxAmount > 250.00)
    {
        priceDiscountAmount = priceAmount * 0.01;
    }
    if (priceDiscountAmount > 15.00)
    {
        charityAmount += priceDiscountAmount * 0.02;
        priceDiscountAmount -= charityAmount;
    }

    // Calculating the new price and the total
    newPriceAmount -= priceDiscountAmount;
    totalAmount += newPriceAmount;
    counter += 1;

    // Showing the user the total and charity amount
    cout << "Total Amount: $" << totalAmount << endl;
    cout << "Charity Amount: $" << charityAmount << endl;

    return 0;
}
