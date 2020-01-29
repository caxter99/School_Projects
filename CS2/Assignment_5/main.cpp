/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 5
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.2.2018
Purpose: The purpose of this program is to display the skills that we learned about lists.
*/

#include <iostream>
#include "charList.hpp"

int main()
{
   // Define a NumberList object.
   charList list;

   // Append some values to the list.
   list.appendNode('t');
   list.appendNode('s');
   list.appendNode('n');
   list.appendNode('m');
   list.appendNode('j');
   list.appendNode('f');
   list.appendNode('c');
   list.appendNode('a');
   list.insertNode('y');
   list.insertNode('0');
   list.insertNode('9');
   list.insertNode('o');
   list.insertNode('p');
   list.insertNode('@');
   list.insertNode('Q');
   list.deleteNode('t');
   list.displayList();
   return 0;
}
