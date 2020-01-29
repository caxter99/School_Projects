/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 8
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 4.10.2018
Purpose: The purpose of this program is to teach us to go through and use binary trees.
*/

#ifndef TREE_HPP
#define TREE_HPP
#include <iostream>
#include "Treenode.hpp"

// Tree class-template definition
template<typename NODETYPE> class Tree {
public:
   // insert node in Tree
   void insertNode(const NODETYPE& value) {
      insertNodeHelper(&rootPtr, value);
   }

   // begin preorder traversal of Tree
   void preOrderTraversal() const {
      preOrderHelper(rootPtr);
   }

   // begin inorder traversal of Tree
   void inOrderTraversal() const {
      inOrderHelper(rootPtr);
   }

   // begin postorder traversal of Tree
   void postOrderTraversal() const {
      postOrderHelper(rootPtr);
   }

   // get the depth of the tree
   int getDepth() const {
      int totalDepth{0};
      int currentDepth{0};

      determineDepth(rootPtr, &totalDepth, &currentDepth);

      return totalDepth;
   }

   // begin binary search
   TreeNode<NODETYPE>* binaryTreeSearch(int val) const {
      return binarySearchHelper(rootPtr, val);
   }

private:
   TreeNode<NODETYPE>* rootPtr{nullptr};

   // utility function called by insertNode; receives a pointer
   // to a pointer so that the function can modify pointer's value
   void insertNodeHelper(TreeNode<NODETYPE>** ptr, const NODETYPE& value) {
      // subtree is empty; create new TreeNode containing value
      if (*ptr == nullptr) {
         *ptr = new TreeNode<NODETYPE>(value);
      }
      else { // subtree is not empty
             // data to insert is less than data in current node
         if (value <= (*ptr)->data) {
            insertNodeHelper(&((*ptr)->leftPtr), value);
         }
         else {
            insertNodeHelper(&((*ptr)->rightPtr), value);
         }
      }
   }

   // utility function to perform preorder traversal of Tree
   void preOrderHelper(TreeNode<NODETYPE>* ptr) const {
      if (ptr != nullptr) {
         std::cout << ptr->data << ' '; // process node
         preOrderHelper(ptr->leftPtr); // traverse left subtree
         preOrderHelper(ptr->rightPtr); // traverse right subtree
      }
   }

   // utility function to perform inorder traversal of Tree
   void inOrderHelper(TreeNode<NODETYPE>* ptr) const {
      if (ptr != nullptr) {
         inOrderHelper(ptr->leftPtr); // traverse left subtree
         std::cout << ptr->data << ' '; // process node
         inOrderHelper(ptr->rightPtr); // traverse right subtree
      }
   }

   // utility function to perform postorder traversal of Tree
   void postOrderHelper(TreeNode<NODETYPE>* ptr) const {
      if (ptr != nullptr) {
         postOrderHelper(ptr->leftPtr); // traverse left subtree
         postOrderHelper(ptr->rightPtr); // traverse right subtree
         std::cout << ptr->data << ' '; // process node
      }
   }

   // calculate the depth of the tree
   void determineDepth(TreeNode<NODETYPE>* treePtr, int* totalD, int* currentD) const {
       // IF the pointer is not pointing to a null value, then there must be more to the tree
       // as well as a current node, so this code checks all that out
       if (treePtr != nullptr)
       {
           // Adding the current depth to the total depth
           *totalD += *currentD;

           // Add one to the current depth, since every line after will be a child of the
           // current node
           *currentD += 1;

           // Start the recursion process by checking the left and right children
           determineDepth(treePtr->leftPtr, totalD, currentD);
           determineDepth(treePtr->rightPtr, totalD, currentD);

           // Making the current depth go back one since there are no more children and the
           // node to get tested will be this node's ancestor, with one less depth than this node
           *currentD -= 1;
       }
   }

   // do a binary search on the Tree
   TreeNode<NODETYPE>* binarySearchHelper(TreeNode<NODETYPE>* treePtr, int value) const {
       // If the binary tree pointer is pointing to a null value then we return the tree pointer
       if (treePtr == nullptr)
       {
           return treePtr;
       }
       // Printing out what I'm comparing so the user knows what's going on
       std::cout << "Comparing " << value << " to " << treePtr->data << ": ";
       if (treePtr->data == value)
       {
           // Letting the user know the search is complete and returning the pointer to the correct TreeNode
           std::cout << "search complete" << std::endl;
           return treePtr;
       }
       // If neither one of the cases are true, then the data in the node is compared to the
       // value the user entered. If the value the user entered is less than the data from the node,
       // then the code searches the node to the left of the current tree node
       else if (value < treePtr->data)
       {
           // Letting the user know the value wasn't found yet, but that the process is still going
           // then using recursion to call this same function
           std::cout << "smaller, walk left" << std::endl;
           return binarySearchHelper(treePtr->leftPtr, value);
       }
       // However, if the value is greater than the data from the tree node, then the code searches
       // the tree node to the right of the current tree node
       std::cout << "larger, walk right" << std::endl;
       return binarySearchHelper(treePtr->rightPtr, value);
    }
};

#endif // TREE_HPP
