/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 6
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.10.2017
Purpose: The purpose of this program is show off our knowledge of templates and stacks.
*/

// This program demonstrates the MathStack class.
#include <iostream>
#include "Stack.hpp"
#include "NumStack.hpp"

int main()
{

   int catchVar;  // To hold values popped off the stack

   // Create a MathStack object.
   Stack<int> stack(5);

   // Push 3 and 6 onto the stack.
   std::cout << "Pushing 3\n";
   stack.push(3);
   std::cout << "Pushing 6\n";
   stack.push(6);

   // Add the two values.
   stack.add();

   // Pop the sum off the stack and display it.
   std::cout << "The sum is ";
   stack.pop(catchVar);
   std::cout << catchVar << std::endl << std::endl;

   // Push 7 and 10 onto the stack
   std::cout << "Pushing 7\n";
   stack.push(7);
   std::cout << "Pushing 10\n";
   stack.push(10);

   // Subtract 7 from 10.
   stack.sub();

   // Pop the difference off the stack and display it.
   std::cout << "The difference is ";
   stack.pop(catchVar);
   std::cout << catchVar << std::endl;

   // Cleaning out the stack to put in my numbers for my tests
   //for (int x = 0; x < 5; ++x)
   //{
       //stack.pop(catchVar);
   //}

   // Loading up the stack to test my functions
   stack.push(4);
   stack.push(5);
   std::cout << "\nPushing 4\n";
   std::cout << "Pushing 5\n";

   // Pop the first two from the stack and multiply them
   stack.mult();
   stack.pop(catchVar);
   std::cout << "The product is " << catchVar << "." << std::endl;

   // Adding some numbers back
   stack.push(2);
   stack.push(4);
   std::cout << "\nPushing 2\n";
   std::cout << "Pushing 4\n";

   // Pop the first two number of the stack and divide them
   stack.div();
   stack.pop(catchVar);
   std::cout << "The quotient is " << catchVar << "." << std::endl;

   //Adding several numbers back, including zero
   stack.push(0);
   stack.push(4);
   stack.push(5);
   stack.push(1);
   std::cout << "\nPushing 0\n";
   std::cout << "Pushing 4\n";
   std::cout << "Pushing 5\n";
   std::cout << "Pushing 1\n";

   // Multiplying them all
   stack.multAll();
   stack.pop(catchVar);
   std::cout << "The product of every number in the stack is " << catchVar << "." << std::endl;

   //Adding several numbers back, not including zero
   stack.push(2);
   stack.push(4);
   stack.push(5);
   stack.push(1);
   std::cout << "\nPushing 2\n";
   std::cout << "Pushing 4\n";
   std::cout << "Pushing 5\n";
   std::cout << "Pushing 1\n";

   // Multiplying them all
   stack.multAll();
   stack.pop(catchVar);
   std::cout << "The product of every number in the stack is " << catchVar << "." << std::endl;

   //Adding several numbers back
   stack.push(2);
   stack.push(0);
   stack.push(5);
   std::cout << "\nPushing 2\n";
   std::cout << "Pushing 0\n";
   std::cout << "Pushing 5\n";

   // Multiplying them all
   stack.addAll();
   stack.pop(catchVar);
   std::cout << "The sum of every number in the stack is " << catchVar << "." << std::endl;

   return 0;
}
