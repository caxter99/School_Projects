/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 2
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.1.2018
Purpose: The purpose of this program is to learn about .hpp and .cpp files and how they link, as well as structs as parameters
*/

// Importing the necessary files and libraries
#include <iostream>
#include "TAX.HPP"
#include "TaxDataType.hpp"
#include "TAX.CPP"
#include "TaxConstants.hpp"

int main()
{
    // Creating my own array, containing two taxPayer structs
    taxPayer taxInformation[SIZE];

    // Getting the tax payer's information
    taxTaker(taxInformation);

    // Printing out the tax payer's information
    taxPrint(taxInformation);

    return 0;
}
