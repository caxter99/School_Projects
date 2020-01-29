
// Guarding the .hpp file

#ifndef NOREPEATS_HPP_INCLUDED
#define NOREPEATS_HPP_INCLUDED
#include "noRepeats.cpp"


std::unique_ptr<char[]> screwRepeats(char originalArray[10])
    {
        // Returning a dynamic array without any repeated letters
        return deleteRepeats(originalArray);
    }

#endif // NOREPEATS_HPP_INCLUDED
