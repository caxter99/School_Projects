/*
   COPYRIGHT (C) 2017 Student Name (UANET ID ) All rights reserved.
   CS assignment
   Author.  Student Name
            zippy@zips.uakron.edu
   Version. 1.01 09.09.2017
   Purpose: This program ...
*/
#include <iostream>

// prototypes
template <class T>
void printarray(const T[], int);
void chew_system_stack();
template <class T>
int part(T[], int, int);
template <class T>
void quicksort(T[], int, int);
void swap(int&, int&);

/*
 * Recursive version of fibonacci
 */
int fibrecurse(int n) {
    // If the number is greater than 1, then a recursive call is required
    if (n > 1)
    {
        return (fibrecurse(n - 1) + fibrecurse(n - 2));
    }

    // If the number is 1, then it can be returned
    else
    {
        return n;
    }

}

/*
 * Iterative (loop) version of fibonacci
 */
int fibiterate(int n) {
    // This sets all the necessary variables to their starting points
    int total = 0, oneBehind = 1, twoBehind = 0;

    // If n is 2 or larger, then the loop is used to get the number
    for (int x = 2; x <= n; ++x)
    {
        total = oneBehind + twoBehind;
        twoBehind = oneBehind;
        oneBehind = total;
    }

    // If n isone, then 1 is given to total to be returned
    if (n == 1)
    {
        ++total;
    }

    // Returning total (which will be 0 if 0 was sent)
    return total;
}

/*
 * Recursive quicksort
 */
template <class T>
void quicksort(T ar[], int first, int last) {
    // Base case, makes sure first is less than the last
    if (first < last)
    {
        // This finds the middle of the array
        int pivotPoint = part(ar, first, last);

        // This is a recursive call to the first half of the array
        quicksort(ar, first, pivotPoint - 1);

        // This is a recursive call to the second half of the array
        quicksort(ar, pivotPoint + 1, last);
    }
}

// This finds the middle, as well as makes sure everything is on the
// appropriate side before the array is separated
template <class T>
int part(T ar[], int first, int last)
{
    // This declares all the necessary variables
    int pivotValue, pivotIndex, mid;

    // this finds the mid point
    mid = (first + last) / 2;

    // The first value and the mid point value are swapped
    swap(ar[first], ar[mid]);

    // This sets the index of the smallest value (from what we've looked at)
    // as well as the index of the value
    pivotIndex = first;
    pivotValue = ar[first];

    // This scans for a value smaller than the pivot value. If it finds
    // one, they're swapped
    for (int scan = first + 1; scan <= last; ++scan)
    {
        if (ar[scan] < pivotValue)
        {
            ++pivotIndex;
            swap(ar[pivotIndex], ar[scan]);
        }
    }

    // Lastly, the first and pivot value are swapped
    swap(ar[first], ar[pivotIndex]);

    // The pivot index (which holds the value of the location of the middle
    // of the array) is returned
    return pivotIndex;
}

// This swaps the two values
void swap(int& one, int& two)
{
    // Swapping the two values
    int temp = one;
    one = two;
    two = temp;
}

int main() {
    const int FIBLOOPS = 10;
    const int ARSIZ = 16;
    int ar[ARSIZ];

    std::cout << "Recursive fib: ";
    for(int i = 0; i < FIBLOOPS; ++i)
    {
        std::cout << fibrecurse(i) << " ";
    }
    std::cout << std::endl;
    std::cout << "Iterative fib: ";
    for(int i = 0; i < FIBLOOPS; ++i)
    {
        std::cout << fibiterate(i) << " ";
    }
    std::cout << std::endl;

    std::cout << "Quicksort:" << std::endl;
    // populate random array
    for(int i = 0; i < ARSIZ; ++i)
    {
        ar[i] = (i * 3037) % 2099;  // prime numbers! again!
    }
    printarray(ar, ARSIZ);
    quicksort(ar, 0, ARSIZ-1);
    printarray(ar, ARSIZ);

    //std::cout << "Chewing system stack:" << std::endl;
    //chew_system_stack();

    return 0;
}

/*  utility functions, do not modify  */
template <class T>
void printarray(const T ar[], int s)
{
    for(int i = 0; i < s; ++i)
    {
        std::cout << ar[i] << " ";
    }
    std::cout << std::endl;
}

void printstackpointer()
{
    void * stack_pointer;
    // inline assembly language to get stack pointer
    __asm__ __volatile__("movl  %%esp,%%eax"
                             :"=a"(stack_pointer)
                             );
    std::cout << stack_pointer << std::endl;
}

void chew_system_stack()
{
    // Feel free to play with this, but please
    // do NOT enable this for your final commit!
    printstackpointer();
    chew_system_stack();
}
/* end utilities */
