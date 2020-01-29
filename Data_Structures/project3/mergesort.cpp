// This is the mergesort.cpp file for Project 3
// Devin Hopkins
// 4190350

#include "mergesort.h"

// Function headers for those not included in mergesort.h
void mergeSort(std::vector<int>& inputData, std::vector<int>& extra, int left, int right);
void merge(std::vector<int>& inputData, std::vector<int>& extra, int left, int center, int right);

void mergeSort(std::vector<int>& inputData)
{
    // creating an additional vector to store the data
    std::vector<int> extra(inputData.size());

    // Actually starting to sort the vector
    mergeSort(inputData, extra, 0, inputData.size() - 1);
}

void mergeSort(std::vector<int>& inputData, std::vector<int>& extra, int left, int right)
{
    // Making sure that the left isn't beyond the right. If so, it can't be divided anymore, nor can
    // it be merged, so it must be stopped. This is also our base case
    if (left < right)
    {
        // Getting the center of the vector
        int center = (right + left) / 2;

        // Dividing the vector into two, this being the left half
        mergeSort(inputData, extra, left, center);

        // Dividing the vector into two, this being the right half
        mergeSort(inputData, extra, center + 1, right);

        // Putting the two vectors together
        merge(inputData, extra, left, center + 1, right);
    }
}

void merge(std::vector<int>& inputData, std::vector<int>& extra, int leftPos, int rightPos, int rightEnd)
{
    // Setting the extra necessary variables
    int leftEnd = rightPos - 1;
    int tempPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    
    // This gets the data in order of smallest first and puts it into the extra vector
    while (leftPos <= leftEnd && rightPos <= rightEnd)
    {
        // If the data in the left position is smaller than the data in the right position, then the data
        // in the left side is put into the extra array
        if (inputData[leftPos] <= inputData[rightPos])
        {
            extra[tempPos++] = std::move(inputData[leftPos++]);
        }
        // Otherwise, the data in th eright position is put into the extra vector
        else
        {
            extra[tempPos++] = std::move(inputData[rightPos++]);
        }
    }

    // At this point in the function, we know that all of the data has been moved out of the right or left
    // part of the main vector. Therefore, we must get the rest of the data from the right or left that has
    // not been moved out must be moved out completely
    //
    // This moves everything in the left vector if the left vector still has some stuff in it
    while (leftPos <= leftEnd)
    {
        extra[tempPos++] = std::move(inputData[leftPos++]);
    }
    // This moves everything in the right vector if the right vector still has some stuff in it
    while (rightPos <= rightEnd)
    {
        extra[tempPos++] = std::move(inputData[rightPos++]);
    }

    // This puts everything in the extra array back into the original array. That's because nothing has actually been
    // changed in the original array, but everything is sorted in the extra vector. This copies everything from the 
    // extra vector to the original vector
    for (int x = 0; x < numElements; ++x, --rightEnd)
    {
        inputData[rightEnd] = std::move(extra[rightEnd]);
    }
}