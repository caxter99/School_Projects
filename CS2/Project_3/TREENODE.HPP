/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 3
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 4.24.2018
Purpose: The purpose of this program is to teach us to go through and use binary trees
        as well as optimize them.
*/

#ifndef TREENODE_HPP
#define TREENODE_HPP

// TreeNode class-template definition.

// forward declaration of class Tree
template<typename NODETYPE> class Tree;

// TreeNode class-template definition
template<typename NODETYPE>
class TreeNode {
   friend class Tree<NODETYPE>;
public:
   // constructor
   TreeNode(const NODETYPE& d) : data{d} {}

   // return copy of node's data
   NODETYPE getData() const {return data;}

   // return a leftPtr
   TreeNode* getLeftPtr() const {
      return leftPtr;
   }

   // return a rightPtr
   TreeNode* getRightPtr() const {
      return rightPtr;
   }

   // set value for leftPtr
   void setLeftPtr(TreeNode* ptr) {
      leftPtr = ptr;
   }

   // set value for rightPtr
   void setRightPtr(TreeNode* ptr) {
      rightPtr = ptr;
   }
private:
   TreeNode<NODETYPE>* leftPtr{nullptr}; // pointer to left subtree
   NODETYPE data;
   TreeNode<NODETYPE>* rightPtr{nullptr}; // pointer to right subtree
};

#endif // TREENODE_HPP
