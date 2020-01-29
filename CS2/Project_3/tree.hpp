/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 3
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 4.24.2018
Purpose: The purpose of this program is to teach us to go through and use binary trees
        as well as optimize them.
*/

#ifndef TREE_HPP
#define TREE_HPP
#include <iostream>
#include <vector>
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
      int currentDepth{-1};

      determineDepth(rootPtr, &totalDepth, &currentDepth);

      return totalDepth;
   }

   // begin binary search
   TreeNode<NODETYPE>* binaryTreeSearch(int val) const {
      return binarySearchHelper(rootPtr, val);
   }

   // traversing the tree in order
    void inOrderTraversalPrint() const {
        std::cout << "\nPrinting out the tree in order: ";
        inOrderTraversalHelper(rootPtr);
        std::cout << std::endl;
    }

    // optimizing the tree
    void optimize()
    {
        // Creating a vector and gathering the values from the tree
        std::vector<NODETYPE> valuesFromTree;
        gatherValues(valuesFromTree, rootPtr);

        // Deleting the entire tree
        deleteFromNode(rootPtr);
        rootPtr = nullptr;

        // Creating new variables for generating the new tree
        int startLocation = 0;
        std::vector<NODETYPE> updatedValues;

        // Puts the values for the new tree in the correct order
        optimizeVector(updatedValues, valuesFromTree, 0, valuesFromTree.size() - 1, &startLocation);

        // Putting in the values in the correct order so the tree is optimized
        for (unsigned x = 0; x < updatedValues.size(); ++x)
        {
            insertNode(updatedValues.at(x));
        }
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

       // If the depth the current node is at is greater than the greatest depth found for the tree
       // so far, then the greatest depth is set to the current depth
       if (*totalD < *currentD)
       {
           *totalD = *currentD;
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

    // Prints out the tree in order using recursion
    void inOrderTraversalHelper(TreeNode<NODETYPE>* treePtr) const
    {
        if (treePtr != nullptr)
        {
            inOrderTraversalHelper(treePtr->leftPtr);
            std::cout << treePtr->data << ' ';
            inOrderTraversalHelper(treePtr->rightPtr);
        }
    }

    // Using recursion, this function gathers all the values from the tree and stores them in
    // the valuesFromTree vector
    void gatherValues(std::vector<NODETYPE>& valuesFromTree, TreeNode<NODETYPE>* treePtr)
    {
        if (treePtr != nullptr)
        {
            valuesFromTree.push_back(treePtr->data);
            gatherValues(valuesFromTree, treePtr->leftPtr);
            gatherValues(valuesFromTree, treePtr->rightPtr);
        }
    }

    // Deleting the entire tree. This function does not set rootPtr to nullptr, however
    void deleteFromNode(TreeNode<NODETYPE>* treePtr)
    {
        if (treePtr != nullptr)
        {
            deleteFromNode(treePtr->leftPtr);
            deleteFromNode(treePtr->rightPtr);
            delete treePtr;
        }
    }

    // This function puts all the values in the newValues vector so that they can be inserted
    // sequentially into the new tree
    void optimizeVector(std::vector<NODETYPE>& newValues, std::vector<NODETYPE>& values, int start,
                        int cutOff, int* locationToInsert)
    {
        // This gets the middle value (which is the value that needs to be put in the front of
        // the new vector)
        int middle = (start + cutOff) / 2;

        // The value from the middle location is put into the new vector
        newValues.push_back(values.at(middle));

        // If the middle is not equal to the beginning or the end, then there must be more data to
        // process, so recursion occurs
        if (middle != start && middle != cutOff)
        {
            // Location to insert goes up by one since a value was just inserted
            *locationToInsert += 1;
            optimizeVector(newValues, values, start, middle - 1, locationToInsert);
            *locationToInsert += 1;
            optimizeVector(newValues, values, middle + 1, cutOff, locationToInsert);
        }
    }
};

#endif // TREE_HPP
