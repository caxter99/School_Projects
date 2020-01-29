#ifndef TAXCONSTANTS_HPP_INCLUDED
#define TAXCONSTANTS_HPP_INCLUDED

// Importing all necessary libraries
#include <limits>

// Making my own namespace, called TAXCONSTANTS
namespace TAXCONSTANTS
{
    // Declaring all necessary constants
    const int SIZE = 2;
    const float MAX_RATE = 9.9;
    const float MIN_RATE = 0.1;
    const float MIN_INCOME = 0.001;
    const float MAX_INCOME = std::numeric_limits<float>::max();
}

#endif // TAXCONSTANTS_HPP_INCLUDED
