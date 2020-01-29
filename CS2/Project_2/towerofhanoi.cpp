/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 2
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 3.19.2018
Purpose: The purpose of this program is use different techniques with queues and dequeues.
*/

// towerofhanoi.cpp : Defines the entry point for the console application.
//DO NOT MODIFY THIS FILE

#include <iostream>
#include "towers.h"

using namespace std;

int main()
{
	int numDisk = 4;
	Towers t(numDisk);
	t.start();
	return 0;
}

