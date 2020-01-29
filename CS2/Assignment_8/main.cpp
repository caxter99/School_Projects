/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 8
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 4.10.2018
Purpose: The purpose of this program is to teach us to go through and use binary trees.
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

   // generate a tree with values
   for (int i{1}; i <= 15; ++i)
   {
      intVal = rand() % 100;
      std::cout << intVal << ' ';
      intTree.insertNode(intVal);
   }

   std::cout << "\n\nEnter a value to search for: ";
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
}
