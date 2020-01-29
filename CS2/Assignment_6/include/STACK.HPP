/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 6
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.10.2017
Purpose: The purpose of this program is show off our knowledge of templates and stacks.
*/

#ifndef STACK_HPP
#define STACK_HPP
#include "NumStack.hpp"

template <class S>
class Stack : public NumStack<int>
{
    public:
        // Constructor
        Stack(S s) : NumStack(s) {}

        // MathStack operations

void mult()
{
    // Declaring my variables
    S first, second;

    // Popping the first two off the stack
    pop(first);
    pop(second);

    // Pushing their product onto the stack
    push(first * second);
}

void div()
{
    // Declaring my variables
    S first, second;

    // Popping the first two off the stack
    pop(first);
    pop(second);

    // Pushing their quotient to the top of the stack
    push(first / second);
}


void addAll()
{
    // Declaring my variables
    S total = 0, number;

    // This loop keeps track of how full the list is, once it's empty it'll quit
    while(!isEmpty())
    {
        // Pops the top off of the list
        pop(number);

        // Adds whatever it popped to the total
        total += number;
    }

    // Pushes the total onto the top of the list
    push(total);
}

void multAll()
{
    // Declaring my variables
    S total = 0, number;
    bool firstTime = true;

    // This loops keeps track of how full the list is, once it's empty it'll quit
    while(!isEmpty())
    {
        // If this is the first time through the loop, changes the total to 1 since it's multiplication
        if (firstTime)
        {
            firstTime = false;
            total = 1;
        }

        // Pops the first number off of the stack
        pop(number);

        // Multiplies the number popped from the stack to the total
        total *= number;
    }

    // Pushes the total to the top of the stack
    push(total);
}

//***********************************************
// Member function add. add pops                *
// the first two values off the stack and       *
// adds them. The sum is pushed onto the stack. *
// pre: no parameters                           *
// post: return the  new stack entry of sum     *
//***********************************************

void add()
{
   S num, sum;

   // Pop the first two values off the stack.
   pop(sum);
   pop(num);

   // Add the two values, store in sum.
   sum += num;

   // Push sum back onto the stack.
   push(sum);
}

//***********************************************
// Member function sub. sub pops the            *
// first two values off the stack. The          *
// second value is subtracted from the          *
// first value. The difference is pushed        *
// onto the stack.                              *
// pre: no parameters                           *
// post: return the  new stack entry of diff    *
//***********************************************

void sub()
{
   S num, diff;

   // Pop the first two values off the stack.
   pop(diff);
   pop(num);

   // Subtract num from diff.
   diff -= num;

   // Push diff back onto the stack.
   push(diff);
}
};

#endif // STACK_HPP_INCLUDED
