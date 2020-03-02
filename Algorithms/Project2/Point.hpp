// Devin Hopkins
// 4190350

#pragma once

// Libraries
#include <iostream>

// My files
// NOTE: DO NOT INCLUDE ANYTHING HERE, THIS IS THE BASE CLASS

// This is my Point Class for Project 2
class Point
{
	public:
		void setPoint(int newX, int newY);
		int getX() { return _x; };
		int getY() { return _y; };
		void displayPoint();

	private:
		int _x, _y;
};