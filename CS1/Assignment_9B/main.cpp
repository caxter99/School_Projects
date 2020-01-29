/*
   COPYRIGHT (C) 20yy Name (UANET ID 9999999) All rights reserved.
   Assignment 9 B - Element Shifter
   Author.  my name
            myUANETID@zips.uakron.edu
   Version. 1.01 mm.dd.20yy
   Purpose:
    This function accepts and integer array and
    the size of the array. It creates a dynamic array one
    element longer and shifts the original array
    by one from the left and sets element 0 to 0.
    Returns a unique pointer to the new dynamic array.


    TECHNICAL NOTES:
    Returns a (unique) pointer to a heap array that this program takes ownership of.
    Program acquires ownership of a uniquely-owned array with dynamic lifetime
    from the elementShifter function
    The use of std::unique_ptr for this program is mainly of intellectual interest

*/

#include <iostream>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::unique_ptr;

unique_ptr<int[]> elementShifter(int , int *);
void showArray(int*, int);

int main()
{
	const int SIZE = 5;
   int myNumbers[SIZE] = {18, 27, 3, 14, 95};

   // Define a unique_ptr smart pointer, pointing
   // to a dynamically allocated array of ints.
   // unique_ptr is a small, fast, move-only smart
   // pointer for managing resources with
   // exclusive-ownership semantics
   unique_ptr<int[]> newCopy(new int[SIZE]);

   showArray(myNumbers, SIZE);

   newCopy = elementShifter(SIZE, myNumbers);

   // Passing the smart pointer as an argument
   showArray(newCopy.std::unique_ptr::release(), SIZE + 1);
   // THIS (ABOVE) IS THE ONLY STATEMENT THAT YOU MAY CHANGE
   // We are required to reuse the same
   // function for displaying

   return 0;
}

// pre-cond: array of ints to expand and the size as an int
// post-cond: pointer to the new allocated array
// Call the element shifter function to make a copy of
// the array, with the elements shifted one
// position toward the end if the array.
unique_ptr<int[]> elementShifter(int arraySize, int* arrayOfInts)
{
    int newSize = arraySize + 1; // The new size
    unique_ptr<int[]> shiftedArray( new int[newSize] );//the new array

    shiftedArray[0] = 0;

    for (auto index = 0; index < arraySize; ++index)
    {
        shiftedArray[index + 1] = *(arrayOfInts + index);
    }

    return shiftedArray;
}

// pre-cond: valid array of integers, and the size as an int
// post-cond: printed array contents
// Display the contents of the array.
void showArray(int *numbers, int size)
{
   cout << "The contents of the array are:\n";
	for (auto index = 0; index < size; ++index)
	{
		cout << *(numbers + index) << " ";
	}
	cout << endl << endl;
}
