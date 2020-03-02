// Devin Hopkins
// 4190350

#pragma once

// Libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// My files
#include "Point.hpp"

// This is my ConvexHull Class for Project 2
class ConvexHull
{
	public:
		void readFile(std::string filename);
		std::vector<Point>* getPointVector() { return &_pointVector; };
		void printPointVector();

	private:
		std::vector<Point> _pointVector;

};