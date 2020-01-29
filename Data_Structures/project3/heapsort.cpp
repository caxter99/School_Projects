// This is the heapsort.cpp file for Project 3
// Devin Hopkins
// 4190350

#include "heapsort.h"

// Function headers for those not included in heapsort.h
void percDown(std::vector<int>& inputData, int i, int n);

// Inline functions not included in heapsort.h
int leftChild(int i) { return 2 * i + 1; } // Gets the child position of the parent sent in

void heapSort(std::vector<int>& inputData)
{
    // This puts every element onto the heap
    for (int x = inputData.size() / 2 - 1; x >= 0; --x)
    {
        percDown(inputData, x, inputData.size());
    }

    for (int y = inputData.size() - 1; y > 0; --y)
    {
        std::swap(inputData[0], inputData[y]);
        percDown(inputData, 0, y);
    }
}

void percDown(std::vector<int>& inputData, int i, int n)
{
    // Setting necessary variables for the function
    int child = 0, temp = 0;

    // Temp starts at the value of the node of i
    // It goes until the left child node's value is less than its parent
    // Everytime the loop iterates, i is set to the child to continue the perculation
    for (temp = std::move(inputData[i]); leftChild(i) < n; i = child)
    {
        // The left child's index is gotten
        child = leftChild(i);

        // IF the child's position is not the last in the heap and the child's value is less
        // than the right child (its sibling), then this if statement is true and the child is
        // incremented
        //
        // The child gets incremented because we want whichever child is larger. So, if it's
        // the right child, then we want to be on the right child. If the it's the left
        // child, we want to stick with the left child
        if (child != n - 1 && inputData[child] < inputData[child + 1])
        {
            ++child;
        }

        // If temp (the value stored by the original parent node) is less than the value of
        // the larger child's node, then this is if statement is true and the value stored in
        // the larger child must go to the node at position i (the original parent's node)
        if (temp < inputData[child])
        {
            inputData[i] = std::move(inputData[child]);
        }
        // If the larger child node's value is smaller or equal to the parent node's value, then
        // there's no need to go any further since the condition of the parent being the largest
        // value (of the parent and two children) is confirmed
        else
        {
            break;
        }
    }

    // This returns position i's node's value to temp
    inputData[i] = std::move(temp);
}