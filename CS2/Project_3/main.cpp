/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 3
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 4.24.2018
Purpose: The purpose of this program is to teach us to go through and use binary trees
        as well as optimize them.
*/

// Assignment 8 Binary Search Tree driver
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tree.hpp"

int main() {
   srand(time(nullptr)); // randomize the random number generator

   Tree<int> intTree;
   int intVal;

   std::cout << "The values being placed in the tree are:\n";

   // filling the tree with the values
   for (int i{1}; i <= 31; ++i)
   {
      std::cout << i << ' ';
      intTree.insertNode(i);
   }

   // Printing out the tree before it's optimized
   std::cout << std::endl << "\nPre-Optimization: ";
   intTree.inOrderTraversalPrint();

   // Printing the depth before it's optimized
   std::cout << "The current depth is: " << intTree.getDepth() << std::endl;

   // Getting the uer's value they want to search
   std::cout << "\nEnter a value to search for: ";
   std::cin >> intVal;

   // create a pointer with the user value
   TreeNode<int>* ptr{intTree.binaryTreeSearch(intVal)};

   // a value is found
   if (ptr != nullptr) {
      std::cout << ptr->getData() << " was found\n";
   }
   else { // value not found
      std::cout << "Element was not found\n";
   }

   std::cout << std::endl;

   // Optimizing the tree
   intTree.optimize();

   // Printing out the tree after it's been optimized
   std::cout << "Post-Optimization: ";
   intTree.inOrderTraversalPrint();

   // Getting the depth of the optimized tree
   std::cout << "The new current depth is: " << intTree.getDepth() << std::endl << std::endl;

   // Searching for the value again, just to show the difference pre and post optimization
   std::cout << "Searching for " << intVal << " again\n";

   // create a pointer with the user value
   TreeNode<int>* ptr2{intTree.binaryTreeSearch(intVal)};

   // a value is found
   if (ptr2 != nullptr) {
      std::cout << ptr2->getData() << " was found\n";
   }
   else { // value not found
      std::cout << "Element was not found\n";
   }
}
