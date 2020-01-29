// This is the insertsort.cpp file for Project 3
// Devin Hopkins
// 4190350

#include "insertsort.h"

void insertionSort(std::vector<int>& inputData)
{
    // This goes through the entire vector
    for (int x = 1; x < inputData.size(); ++x)
    {
        // This gets the value at position x
        int nextVal = std::move(inputData[x]);
        int y = 0;

        // This goes through all of the values starting from position x to position 0.
        // This keeps going until a value in the spot before (closer to the front of the
        // vector) is smaller than the value who's location is trying to be determined.
        // Since everything prior to position x has already been sorted, we can do this
        for (y = x; y > 0 && nextVal < inputData[y - 1]; --y)
        {
            inputData[y] = std::move(inputData[y - 1]);
        }

        // At the end, the value must be put into position y (where it was determined it
        // would fit to make it ascending)
        inputData[y] = std::move(nextVal);
    }
}