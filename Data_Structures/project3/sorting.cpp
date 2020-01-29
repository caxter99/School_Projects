// This is the sorting.cpp file for Project 3
// Devin Hopkins
// 4190350

#include "heapsort.h"
#include "insertsort.h"
#include "mergesort.h"
#include "quicksort.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <math.h>

// Function headers
//
// This returns a string that makes the integer look nice
std::string intToNiceString(int);
// This prints the contents of the vector
void displayVector(std::vector<int>&);
// Resets the vector to its original condition (first vector is getting reset, second is the mold)
void resetVector(std::vector<int>&, std::vector<int>&);
// Fills a vector with the specified number of ints in order
void fillVectorInOrder(std::vector<int>&, int);
// Fills a vector with the specified number of ints in reverse order
void fillVectorInRevOrder(std::vector<int>&, int);
// Fills a vector with the specified number of ints in random order
void fillVectorInRandOrder(std::vector<int>&, int);
// Deletes all of the contents of the vector
void deleteVector(std::vector<int>&);

int main(int argc, char const *argv[])
{
    // THIS SECTION IS FOR TESTING ONLY

    //std::string input = "sorting_test.dat";
    //int N = 100000000;

    // THIS IS THE END OF THE TESTING SECTION

    // THIS IS THE REPLACEMENT FOR THE TESTING ONLY SECTION

    // Getting the file name that the user wants to process
    std::string input = "", toBecomeInt = "";
    std::cout << "\nPlease enter the filename: ";
    std::getline(std::cin, input);
    std::cout << "Enter the number of integers to sort: ";
    std::getline(std::cin, toBecomeInt);
    int N = std::stoi(toBecomeInt);

    // THIS IS THE END OF THE REPLACEMENT FOR THE TESTING ONLY SECTION

    std::vector<int> inputData(N);
    std::vector<int>copyOfInputData(N);

    // Creating clocks
    clock_t start, end;

    // Creating the input object to gather the data from the file
    std::ifstream inputfile;
    inputfile.open(input);
    
        // Making sure the file was actually opened
    if (inputfile)
    {
        // Telling the user what's going on
        std::cout << "\n\nReading data in from the file and sorting it:" << std::endl;

        // Creating necessary variables
        std::string lineFromFile = "";
        std::vector<int> inputData = {}; // This is the vector that will be sorted
        std::vector<int> copyOfInputData = {}; // This is the vector that won't be changed

        // Getting the data from the input file
        while (getline(inputfile, lineFromFile))
        {
            inputData.push_back(stoi(lineFromFile));
        }

        // Creating the copy of the vector
        resetVector(copyOfInputData, inputData);

        //
        // MERGE SORT
        //
        
        // Showing the vector to the user before it's sorted
        std::cout << "vector before merge sort: ";
        displayVector(inputData);

        // Sorting the vector
        mergeSort(inputData);

        // Showing the vector to the user after it's sorted
        std::cout << " vector after merge sort: ";
        displayVector(inputData);

        //
        // HEAP SORT
        //

        // Resetting the vector and output space
        resetVector(inputData, copyOfInputData);
        std::cout << std::endl;

        // Showing the vector to the user before it's sorted
        std::cout << "vector before heap sort: ";
        displayVector(inputData);

        // Sorting the vector
        heapSort(inputData);

        // Showing the vector to the user after it's sorted
        std::cout << " vector after heap sort: ";
        displayVector(inputData);

        //
        // QUICK SORT
        //

        // Resetting the vector and output space
        resetVector(inputData, copyOfInputData);
        std::cout << std::endl;

        // Showing the vector to the user before it's sorted
        std::cout << "vector before quick sort: ";
        displayVector(inputData);

        // Sorting the vector
        quickSort(inputData);

        // Showing the vector to the user after it's sorted
        std::cout << " vector after quick sort: ";
        displayVector(inputData);

        //
        // INSERTION SORT
        //

        // Resetting the vector and output space
        resetVector(inputData, copyOfInputData);
        std::cout << std::endl;

        // Showing the vector to the user before it's sorted
        std::cout << "vector before insertion sort: ";
        displayVector(inputData);

        // Sorting the vector
        insertionSort(inputData);

        // Showing the vector to the user after it's sorted
        std::cout << " vector after insertion sort: ";
        displayVector(inputData);

        std::cout << std::endl;
    }
    else
    {
        std::cout << "\n\nThe file " << input << " could not be opened.\n" << std::endl;
    }

    // Making sure the output looks nice
    std::cout << "\n";

    // This goes to make sure we get in order sorts, reverse order sorts, and random sorts with
    // N elements
    for (int x = 0; x < 3; ++x)
    {
        // This is so the user knows what's being tested.
        // This also creates the vector
        switch(x) {
            case 0: //std::cout << "Using a vector with " << intToNiceString(N) << " elements in order:" << std::endl;
                    std::cout << "Using a vector with " << N << " elements in order:" << std::endl;
                    fillVectorInOrder(inputData, N); // In order
                    break;
            case 1: //std::cout << "Using a vector with " << intToNiceString(N) << " elements in reverse order:" << std::endl;
                    std::cout << "Using a vector with " << N << " elements in reverse order:" << std::endl;
                    fillVectorInRevOrder(inputData, N); // In reverse order
                    break;
            case 2: //std::cout << "Using a vector with " << intToNiceString(N) << " elements in random order:" << std::endl;
                    std::cout << "Using a vector with " << N << " elements in random order:" << std::endl;
                    fillVectorInRandOrder(inputData, N); // In random order
        }
    
        // Creating the copy of the vector
        resetVector(copyOfInputData, inputData);
    
        //
        // HEAP SORT
        //
    
        // Resetting the vector and output space
        resetVector(inputData, copyOfInputData);
    
        // Getting the clock ticks before the algorithm starts
        start = clock();
    
        // Sorting the vector
        heapSort(inputData);
    
        // Getting the clock ticks after the algorithm ends
        end = clock();
    
        // Displaying it to the user
        std::cout << "Heap Sort Runtime: " << double(end - start) / double(CLOCKS_PER_SEC) << std::endl;
                
        //
        // MERGE SORT
        //
    
        // Getting the clock ticks before the algorithm starts
        start = clock();
    
        // Sorting the vector
        mergeSort(inputData);
    
        // Getting the clock ticks after the algorithm ends
        end = clock();
    
        // Displaying it to the user
        std::cout << "Merge Sort Runtime: " << double(end - start) / double(CLOCKS_PER_SEC) << std::endl;
    
        //
        // QUICK SORT
        //
    
        // Resetting the vector and output space
        resetVector(inputData, copyOfInputData);

        // Getting the clock ticks before the algorithm starts
        start = clock();

        // Sorting the vector
        quickSort(inputData);

        // Getting the clock ticks after the algorithm ends
        end = clock();
    
        // Displaying it to the user
        std::cout << "Quick Sort Runtime: " << double(end - start) / double(CLOCKS_PER_SEC) << std::endl;
        
        //
        // INSERTION SORT
        //
    
        // Resetting the vector and output space
        resetVector(inputData, copyOfInputData);
    
        // Making sure the vector is small enough to be able to use quick sort on it
        if (N <= 250000)
        {
            // Getting the clock ticks before the algorithm starts
            start = clock();

            // Sorting the vector
            insertionSort(inputData);

            // Getting the clock ticks after the algorithm ends
            end = clock();
    
            // Displaying it to the user
            std::cout << "Insertion Sort Runtime: " << double(end - start) / double(CLOCKS_PER_SEC) << std::endl;
        }
        else
        {
            std::cout << "Sorry, " << N << " is too large of a number to use insertion sort. (must be <= 250,000)\n";
            std::cout << "It would work, but it takes too long and my computer kept crashing so it got canned." << std::endl;
        }

        // Making sure the output stays nice
        std::cout << std::endl;
    }

    return 0;
}

// Resets the vector to its original condition (first vector is getting reset, second is the mold)
void resetVector(std::vector<int>& vecToReset, std::vector<int>& vecMold)
{
    // Getting rid of all the elements in the first vector
    for (int x = vecToReset.size(); x > 0; --x)
    {
        vecToReset.pop_back();
    }

    // Getting all of the elements from the vecMold vector to the original vector
    for (int x = 0; x < vecMold.size(); ++x)
    {
        vecToReset.push_back(vecMold[x]);
    }
}

// This prints the contents of the vector
void displayVector(std::vector<int>& vec)
{
    for (std::vector<int>::iterator vIter = vec.begin(); vIter != vec.end(); ++vIter)
    {
        std::cout << (*vIter) << " ";
    }
    std::cout << "\n";
}

// Fills a vector with the specified number of ints in order
void fillVectorInOrder(std::vector<int>& toFill, int fillStop)
{
    // Making sure the vector is empty
    deleteVector(toFill);

    // Filling the vector
    for (int x = 0; x < fillStop; ++x)
    {
        toFill.push_back(x);
    }
}

// Fills a vector with the specified number of ints in reverse order
void fillVectorInRevOrder(std::vector<int>& toFill, int fillStart)
{
    // Making sure the vector is empty
    deleteVector(toFill);

    // Filling the vector
    for (int x = fillStart - 1; x >= 0; --x)
    {
        toFill.push_back(x);
    }
}

// Fills a vector with the specified number of ints in random order
void fillVectorInRandOrder(std::vector<int>& toFill, int fillStop)
{
    // Making sure the vector is empty
    deleteVector(toFill);

    // Seeding the random time
    srand(time(0));

    // Creating the integer variable
    int randNum = 0;

    // Filling the vector
    for (int x = 2; x < fillStop + 2; ++x)
    {
        randNum = rand() % x;
        toFill.push_back(randNum);
        //toFill.push_back((rand() % x) + ((2 * rand()) % (x - 1)));
    }
}

// Deletes all of the contents of the vector
void deleteVector(std::vector<int>& vec)
{
    // Deleting the vector
    for (int x = vec.size() - 1; x >= 0; --x)
    {
        vec.pop_back();
    }
}

// This returns a string that makes the integer look nice
std::string intToNiceString(int intToConvert)
{
    // Creating the string that will be returned
    std::string newString = "";

    // If the number is less than four digits long, then nothing needs to
    // be done, so it's returned as is in string form
    if (intToConvert < 1000)
    {
        newString = intToConvert;
        return newString;
    }

    // This counting the number of digits the number has (excluding the 4 we
    // know it has)
    int numOfDigits = 4;
    int intToConvertDuplicate = intToConvert / 1000; // Shaving off the right four
                                                     // digits using integer division

    while (intToConvertDuplicate > 0)
    {
        // Getting rid of the right most digit
        intToConvertDuplicate /= 10;

        // Increasing the digit count by one
        numOfDigits += 1;

        std::cout << "HERE" << std::endl;
    }

    std::cout << numOfDigits << std::endl;

    while(numOfDigits > 3);
    {
        std::cout << "HERE" << std::endl;

        int temp = (intToConvert / pow(10, numOfDigits));
        // Adding the first three digits to the string
        newString += temp;
        newString += ",";

        // Shaving off the top three digits of the integer
        intToConvert = intToConvert - (intToConvert / pow(10, numOfDigits));

        // Decreasing the number of digits by three
        numOfDigits -= 3;
    }

    // Returning the string that has commas in the right place (making it look nice)
    return newString;
}