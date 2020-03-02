// Devin Hopkins
// 4190350

#pragma once

// Libraries
#include <iostream>

// This is my Point Class for Project 2
class Point
{
	public:
		void setPoint(int newX, int newY);
		int getX() { return x; };
		int getY() { return y; };
		void displayPoint();

	private:
		int x, y;
};