// This is the quicksort.cpp file for Project 3
// Devin Hopkins
// 4190350

#include "quicksort.h"

// Function headers not included in the quicksort.h file
int& median3(std::vector<int>& inputData, int left, int right);
void quickSort(std::vector<int>& inputData, int left, int right);

void quickSort(std::vector<int>& inputData)
{
    // Performing the actual quick sort
    quickSort(inputData, 0, inputData.size() - 1);
}

void quickSort(std::vector<int>& inputData, int left, int right)
{
    // If the vector needing to be sorted is less than 2 in size, then a simple check will
    // make sure that they're in order
    if (right - left < 2)
    {
        // If they're out of order, then they're swapped
        if (inputData[right] < inputData[left])
        {
            std::swap(inputData[left], inputData[right]);
        }
    }
    // If there's more than two elements needing to be sorted, they go in here
    else if (left < right)
    {
        // This gets the pivot point
        int& pivot = median3(inputData, left, right);

        // This simply sets up the the values of i and j
        int i = left, j = right - 1;

        // An infinite loop, but there's a break inside.
        // Necessary for
        for ( ; ; )
        {
            // This finds the first value on the left side that's greater than the pivot and
            // stores its location in spot i
            while (inputData[++i] < pivot) {}

            // This finds the first value on the right side that's smaller than the pivot value
            // and stores it in spot j
            while (pivot < inputData[--j]) {}

            // If i is less than j, meaning that the smaller element is in a location that's
            // greater than the greater element, and thus they need to be swapped
            if (i < j)
            {
                std::swap(inputData[i], inputData[j]);
            }
            // If they're in their proper spot, they are left alone
            else
            {
                break;
            }
        }

        // This puts the pivot back in its proper place
        std::swap(inputData[i], inputData[right - 1]);

        // This does the left and right side using the same algorithm
        quickSort(inputData, left, i - 1);
        quickSort(inputData, i + 1, right);
    }
}

int& median3(std::vector<int>& inputData, int left, int right)
{
    // This is getting the center element
    int center = (left + right) / 2;

    // If the element in the center is less than the element on the left, then they're swapped
    if (inputData[center] < inputData[left])
    {
        std::swap(inputData[left], inputData[center]);
    }
    
    // If the element on the right is less than the element on the left, then they're swapped
    if (inputData[right] < inputData[left])
    {
        std::swap(inputData[left], inputData[right]);
    }

    // If the element on the right is less than the element in the center, then they're swapped
    if (inputData[right] < inputData[center])
    {
        std::swap(inputData[center], inputData[right]);
    }

    // This puts the pivot value at right - 1
    std::swap(inputData[center], inputData[right - 1]);

    // This returns the pivot value
    return inputData[right - 1];
}