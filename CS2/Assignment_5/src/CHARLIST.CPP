/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 5
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.2.2018
Purpose: The purpose of this program is to display the skills that we learned about lists.
*/

/*
   COPYRIGHT (C) 2016 Student Name (UANET ID ) All rights reserved.
   CSII assignment 5 A
   Author.  Student Name
            zippy@zips.uakron.edu
   Version. 1.01 09.09.2017

*/
// Implementation file for the NumberList class

// Your coding required here
#include "charList.hpp"
#include <iostream>

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
// pre: an empty parameter list                    *
// post: standard output of the linked list        *
//**************************************************

void charList::displayList() const
{
   ListNode *nodePtr;  // To move through the list

   // Position nodePtr at the head of the list.
   nodePtr = head;
   short count = 0;

   // While nodePtr points to a node, traverse
   // the list.
   while (nodePtr)
   {
      // Display the value in this node.
      std::cout << "[" << nodePtr->value << "] -> ";
      ++count;
      // Move to the next node.
      nodePtr = nodePtr->next;
      if (count % 10 == 0) {
        std::cout << std::endl;
        count = 0;
      }
   }
   std::cout << std::endl;
}

// PRE: This function expects a character
// POST: The character will be added to the end of the linked list
void charList::appendNode(char character)
{
    // Creating the new node
    ListNode* newNode = new ListNode;
    newNode->value = character;
    newNode->next = nullptr;

    // Checking to make sure there's already a node in the stack, if not, the first is created and the function
    // is done
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    // If there are already some nodes, then we need to find the last node
    ListNode* lastNode = head;
    while(lastNode->next != nullptr)
    {
        lastNode = lastNode->next;
    }

    // This sets the last node's pointer to the new node
    lastNode->next = newNode;
}

// PRE: This function expects a character that will be put into the linked list in appropriate, descending order
// POST: The character given will be inserted into the linked list while maintaining the linked list descending order
void charList::insertNode(char character)
{
    // Creating a new node
    ListNode* newNode = new ListNode;
    newNode->value = character;
    newNode->next= nullptr;

    // Checking to make sure this isn't the first node in the stack. If it is, the function is over and the new
    // character becomes the first element
    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    // Finding out where the new node belongs
    ListNode* oneTooFarNode = head;

    // If the stack contains more than one element, then the following if statement will be executed
    if (head->next != nullptr)
    {
        oneTooFarNode = head->next;
    }

    // If the stack only contains one element, this code is executed. After executing this block of code,
    // the function then ends
    else
    {
        // This makes sure the list stays in descending order
        if (oneTooFarNode->value > character)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            head = newNode;
        }
        return;
    }

    // If the list contains more than one element, than the code goes into here to find out where the new
    // node belongs
    ListNode* correctNode = head;
    while(oneTooFarNode != nullptr && oneTooFarNode->value > character)
    {
        correctNode = oneTooFarNode;
        oneTooFarNode = oneTooFarNode->next;
    }

    // If the new node belongs anywhere but the beginning, then this is where the code goes and places
    // the new node in the correct spot
    if (correctNode != head)
    {
        correctNode->next = newNode;
        newNode->next = oneTooFarNode;
    }

    // If the new node belongs at the beginning, this is where the code goes and places the new node at
    // the beginning
    else
    {
        newNode->next = head;
        head = newNode;
    }
}

// PRE: The function expects a character that may or may not be in the linked list
// POST: If the linked list contains the character, that node is deleted. If the character is not in the linked list,
//       then nothing happens
void charList::deleteNode(char character)
{
    // Checks to see if there are any elements in the list at all. If not, quits the function
    if (head == nullptr)
    {
        return;
    }
    // If the node the head points to contains the value trying to be deleted, it is taken care of immediately and
    // the function is ended directly afterward
    else if (head->value == character)
    {
        ListNode* temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
        return;
    }

    // If the node to be deleted is somewhere within the list, it is searched for, starting here
    ListNode* needToBeGoneNode = head->next;
    ListNode* previousNode = head;

    // This while loop finds the node that needs to be deleted
    while(needToBeGoneNode != nullptr && needToBeGoneNode->value != character)
    {
        previousNode = needToBeGoneNode;
        needToBeGoneNode = needToBeGoneNode->next;
    }

    // If the node that needs to be deleted does not exist, then the function exits with no harm done to
    // the actual list
    if (needToBeGoneNode == nullptr)
    {
        return;
    }

    // If the node that needs to be deleted was found, it is taken care of here. This leaves no linked part
    // of the list broken and no memory clogged up
    previousNode->next = needToBeGoneNode->next;
    needToBeGoneNode->next = nullptr;
    delete needToBeGoneNode;
}


//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
// pre: n/a                                        *
// post: destroyed object                          *
//**************************************************

charList::~charList()
{
   ListNode *nodePtr;   // To traverse the list
   ListNode *nextNode;  // To point to the next node

   // Position nodePtr at the head of the list.
   nodePtr = head;

   // While nodePtr is not at the end of the list...
   while (nodePtr != nullptr)
   {
      // Save a pointer to the next node.
      nextNode = nodePtr->next;

      // Delete the current node.
      delete nodePtr;

      // Position nodePtr at the next node.
      nodePtr = nextNode;
   }
}
