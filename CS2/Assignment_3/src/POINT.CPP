/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 3
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.12.2018
Purpose: The purpose of this program is teach the use of classes and functions, as well as program a rectangle validation program
*/

// Including all necessary files
#include "Point.hpp"

// Default constructor, will set the points to (0, 0)
Point::Point()
{
    x = 0.0;
    y = 0.0;
}

// This constructor takes two floats, which will become the coordinates of the point
Point::Point(float one, float two)
{
    x = one;
    y = two;
}

// PRE: None
// POST: Returns a float with the value of the x coordinate given to the point
float Point::getX()
{
    return x;
}

// PRE: None
// Post: Returns a float with the value of the y coordinate given to the point
float Point::getY()
{
    return y;
}
