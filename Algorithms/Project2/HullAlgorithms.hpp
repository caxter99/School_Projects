// Devin Hopkins
// 4190350

#pragma once

// Libraries
#include <iostream>
#include <stack>
#include <vector>

// My files
#include "Point.hpp"
#include "ConvexHull.hpp"

// This is my HullAlgorithms Class for Project 2
class HullAlgorithms
{
	public:
		std::stack<Point> doGrahamScan(std::vector<Point>* points);
		std::stack<Point> doJarvisMarch(std::vector<Point>* points);
		std::stack<Point> doQuickHull(std::vector<Point>* points);

	private:
		Point* getLowestPoint(std::vector<Point>* points); // Returns a reference to the lowest point
		float findSlope(Point* one, Point* two); // Returns the slope given two points
		void sortPointsOnSlope(std::vector<Point>* points, Point* basePoint); // Sorts the points based on their slope relative to the base point
		void quickSortSlope(std::vector<Point>* arr, int low, int high, Point* basePoint); // Quicksorting algorithm based on slope
		int partitionSlope(std::vector<Point>* arr, int low, int high, Point* basePoint); // Partitioning based on slope
		void swap(Point* a, Point* b); // Swaps two points
};