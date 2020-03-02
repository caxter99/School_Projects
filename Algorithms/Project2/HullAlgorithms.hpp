// Devin Hopkins
// 4190350

#pragma once

// Libraries
#include <iostream>
#include <stack>

// My files
#include "Point.hpp"
#include "ConvexHull.hpp"

// This is my HullAlgorithms Class for Project 2
class HullAlgorithms
{
	public:
		std::stack<Point> doGrahamScan();
		std::stack<Point> doJarvisMarch();
		std::stack<Point> doQuickHull();

	private:
		// None (at least right now, maybe forever)
};