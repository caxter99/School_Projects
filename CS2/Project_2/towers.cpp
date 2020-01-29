/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 2
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.19.2018
Purpose: The purpose of this program is use different techniques with queues and dequeues.
*/

#include <iostream>
#include "towers.h"
#include "mystack.h"

using namespace std;
//YOUR CODE
//......

/*
PRE: Expects an integer that contains the number of disks in the tower
POST: Creates a Towers object with three pegs, all of which can hold all the disks should it be required
*/
Towers::Towers(int numberOfDisks)
{
    // Declaring and initializing variables and objects
    numDisk = numberOfDisks;
    peg1 = new MyStack<int>(numDisk);
    peg2 = new MyStack<int>(numDisk);
    peg3 = new MyStack<int>(numDisk);

    // Setting the disks
    setDisks();
}

/*
PRE: None
POST: Deletes the Towers object
*/
Towers::~Towers()
{
    numDisk = 0;
    delete peg1;
    delete peg2;
    delete peg3;
}

/*
PRE: Expects an integer that contains the number of disks to be moved, and then three MyStack vectors
POST: Moves the disks from the first peg to the third peg, following the rules
*/
void Towers::move(int n, MyStack<int>* s, MyStack<int>* t, MyStack<int>* d)
{
    // This is the base case
    // If there's only one move to be done, the move is made
    if (n == 1)
    {
        moveOne(s, d);
    }

    // If there's more than one move to go, then recursion happens in here
    else
    {
        // n - 1: One more move is being done, so the total number of moves remaining decreases by one
        // s: For the first set of moves (moving all the disks off of the starting peg), so s (the starting
        //    peg) remains the same
        // d: Because every other peg will need to alternate which peg it goes to (the first disk to the t peg,
        //    the second one to the d peg, then the next disk to the t peg, etc), so the d and t peg switch
        // t: See d's comment
        move(n - 1, s, d, t);

        // This line is necessary to move the bottom disk from the original peg to the destination peg
        move(1, s, t, d);

        // See the first several comments in this block, it's the exact same, only now the starting peg acts
        // as the middle, temporary peg (so switch the s and t comments above)
        move(n - 1, t, s, d);
    }
}

/*
PRE: Expects a Towers object
POST: Creates a new Towers object, copying from the original Towers object
*/
Towers::Towers(const Towers &right)
{
    // Copying the number of disks to the new object
    numDisk = right.numDisk;

    // Creating three new vectors for the new object
    peg1 = new MyStack<int>(numDisk);
    peg2 = new MyStack<int>(numDisk);
    peg3 = new MyStack<int>(numDisk);

    // Copying each element of the object in the parenthesis to the new object
    for (int x = 0; x < numDisk; ++x)
    {
        peg1[x] = right.peg1[x];
        peg2[x] = right.peg2[x];
        peg3[x] = right.peg3[x];
    }
}

/*
PRE: Expects a Towers object
POST: Creates a new Towers object, copying from the original Towers object
*/
Towers& Towers::operator=(const Towers &right)
{
    // If they're different, then the object on the left gets replaced with data from the
    // object on the left
    if (this != &right)
    {
        numDisk = right.numDisk;
        peg1 = right.peg1;
        peg2 = right.peg2;
        peg3 = right.peg3;

        return *this;
    }

    // If they're the same, then it's just returned and nothing is changed
    return *this;
}

/*
PRE: None
POST: Getting rid of all the old disks and replacing them with new disks on peg one
*/
void Towers::setDisks()
{
    // Getting rid of any previous values in the pegs
    for (int x = 0; x < numDisk; ++x)
    {
        peg1->pop();
        peg2->pop();
        peg3->pop();
    }

    // Filling the first peg with the necessary integers
    for (int x = 0; x < numDisk; ++x)
    {
        peg1->push(numDisk - x);
    }

    // Printing out the work
    plotPegs();
}

/*
PRE: Expects two MyStack vectors, the first one being the stack that is going to have a
    disk removed and the second one being the vectors that will have that same disk
    added to it
POST: Prints out the new line up of disks
*/
void Towers::moveOne(MyStack<int>* s, MyStack<int>* d)
{
    // Taking the disk off the the first vector and onto the second
    d->push(s->pop());

    // Displaying what's been done
    plotPegs();
}


//Display disks on the three pegs in the console window (stdout)
//DO NOT MODIFY THIS FUNCTION
void Towers::plotPegs()
{
  	if (peg1==NULL || peg2==NULL || peg3==NULL) return;

	int n1=peg1->size();
	int n2=peg2->size();
	int n3=peg3->size();
	int numDisk = n1+n2+n3;

	MyStack<int> tmp1(*peg1);
	MyStack<int> tmp2(*peg2);
	MyStack<int> tmp3(*peg3);

	//plot
	for (int i=0; i<numDisk; i++) {
		//peg1
		if (numDisk-n1-i>0) {
			for (int j=0; j<numDisk; j++)
				cout << " ";
		}
		else {
			int m1 = tmp1.top();
			tmp1.pop();
			for (int j=0; j<m1; j++)
				cout << "*";
			for (int j=m1; j<numDisk; j++)
				cout << " ";
		}
		cout <<" | ";

		//peg2
		if (numDisk-n2-i>0) {
			for (int j=0; j<numDisk; j++)
				cout << " ";
		}
		else {
			int m2 = tmp2.top();
			tmp2.pop();
			for (int j=0; j<m2; j++)
				cout << "*";
			for (int j=m2; j<numDisk; j++)
				cout << " ";
		}
		cout <<" | ";

		//peg3
		if (numDisk-n3-i>0) {
			for (int j=0; j<numDisk; j++)
				cout << " ";
		}
		else {
			int m3 = tmp3.top();
			tmp3.pop();
			for (int j=0; j<m3; j++)
				cout << "*";
			for (int j=m3; j<numDisk; j++)
				cout << " ";
		}
		cout<<endl;
	}
	cout << "_________________________________________\n";
}
