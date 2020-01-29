/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 2
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.19.2018
Purpose: The purpose of this program is use different techniques with queues and dequeues.
*/

#ifndef MYSTACK_H
#define MYSTACK_H

//***************************************//
//static stack template                  //
//finish all functions                   //
//***************************************//

#include <iostream>
using namespace std;

template <class T>
class MyStack
{
private:
   T *stackArray;  // Pointer to the stack array
   int stackSize;    // The stack size
   int numElem;		//index of the top element in the stack array

public:
   // Constructor
   MyStack(int);	//pass in an int: tells the maximum size of the stack

   // Copy constructor
   MyStack(const MyStack &);

   //operator= overloading
   MyStack& operator=(const MyStack &);

   // Destructor
   ~MyStack();

   // Stack operations
   void push(T);	//add an item to the stack by passing in a value
   T pop();	//pop a value out by returning the value
   T top();	//return the value at the top position in the stack
   bool isFull() const;	//tell if the stack is full
   bool isEmpty() const;	//tell if the stack is empty
   int size() const;	//tell how many items are in the stack
};

//YOUR CODE
//......

/*
PRE: Nothing
POST: Deletes everything in the object and resets all other variables
*/
template <class T>
MyStack<T>::~MyStack()
{
    // Deleting all variables and resetting others
    delete [] stackArray;
    stackSize = 0;
    numElem = 0;
}

/*
PRE: Expects a MyStack object
POST: Returns a MyStack object
*/
template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T> &right)
{
    // If they're not equal, then the code goes in here
    if (this != &right)
    {
        // Transferring the stack size and number of elements from the object on the right to
        // the object on the left
        stackSize = right.stackSize;
        numElem = right.numElem;

        // Creating a new stack array for the object on the left and copying every item from the
        // object on the right to the object on the left
        stackArray = new T[stackSize];
        for (int x = 0; x < stackSize; ++x)
        {
            stackArray[x] = right.stackArray[x];
        }

        // Returning the new MyStack object
        return *this;
    }

    // If they're equal, then the object on the left is returned without any modifications
    return *this;
}

/*
PRE: Expects a MyStack object
POST: Creates another MyStack object
*/
template <class T>
MyStack<T>::MyStack(const MyStack &right)
{
    // Setting the new object's values to the object on the right's values
    stackSize = right.stackSize;
    numElem = right.numElem;

    // Creating and copying the stack array from the right object to the object in the parenthesis
    stackArray = new T[stackSize];
    for (int x = 0; x < stackSize; ++x)
    {
        stackArray[x] = right.stackArray[x];
    }
}

/*
PRE: Expects an integer
POST: This sets the size of the MyStack's stack array to the integer and initializes all
       values to 0
*/
template <class T>
MyStack<T>::MyStack(int sizeOfStack)
{
    // Setting the size of the stack and the number of elements
    stackSize = sizeOfStack;
    numElem = -1; // This is -1 instead of 0 because 0 represents the first element
    stackArray = new T[sizeOfStack];

    // Setting the new stack's contents to 0
    for (int x = 0; x < sizeOfStack; ++x)
    {
        stackArray[x] = 0;
    }
}

/*
PRE: Expects data of the same type that the MyStack object is created in
POST: This puts the data on top of the stack, so long as the stack's not already full
*/
template <class T>
void MyStack<T>::push(T data)
{
    // Putting data on top of the stack, so long as it's not full and the data isn't 0
    if (!isFull() && data != 0)
    {
        // It also increases the number of elements in the stack by one
        ++numElem;
        stackArray[numElem] = data;
    }
}

/*
PRE: None
POST: Returns the data off of the top of the stack
*/
template <class T>
T MyStack<T>::pop()
{
    // Creating a temporary data type
    T temp = 0;

    // If the stack is not empty, then the top data is taken off
    if (!isEmpty())
    {
        temp = stackArray[numElem];
        stackArray[numElem] = 0;

        // The number of elements is also decreased by one
        --numElem;
    }

    // Returning the data popped of the top (0 if nothing was popped)
    return temp;
}

/*
PRE: None
POST: Returns the data on top of the stack
*/
template <class T>
T MyStack<T>::top()
{
    return stackArray[numElem];
}

/*
PRE: None
POST: Returns true if the stack is full, false if not
*/
template <class T>
bool MyStack<T>::isFull() const
{
    // Since the number of elements variables is one less than the actual number of elements,
    // it needs to be increased by one to see if the max number of elements is held
    return (numElem + 1 == stackSize);
}

/*
PRE: None
POST: Returns true if the stack is empty, false otherwise
*/
template <class T>
bool MyStack<T>::isEmpty() const
{
    // Since -1 means the stack is empty, this is true if the stack is empty
    return (numElem == -1);
}

/*
PRE: None
POST: Returns the number of elements in the stack
*/
template <class T>
int MyStack<T>::size() const
{
    // Since the number of elements is one less than the actual number of elements, it must be
    // increased by one before being returned
    return (numElem + 1);
}

#endif
