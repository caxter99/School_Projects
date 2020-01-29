#ifndef TAX_HPP_INCLUDED
#define TAX_HPP_INCLUDED

// Importing all necessary files
#include "TaxDataType.hpp"

// PRE: Expects an array with taxPayer structs
// POST: Prints out the taxes each taxPayer owes
void taxPrint(taxPayer infoArray[]);

// PRE: Expects an array with taxPayer structs
// POST: Will have all the taxPayer structs filled by asking the user to input all the necessary stats
void taxTaker(taxPayer infoArray[]);

#endif // TAX_HPP_INCLUDED
