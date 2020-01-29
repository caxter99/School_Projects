/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 3
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.12.2018
Purpose: The purpose of this program is teach the use of classes and functions, as well as program a rectangle validation program
*/

#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED

class Point
{
private:
    float x, y;

public:
    Point();
    Point(float, float);
    float getX();
    float getY();
};

#endif // POINT_HPP_INCLUDED
