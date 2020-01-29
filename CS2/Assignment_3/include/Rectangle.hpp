/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 3
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.12.2018
Purpose: The purpose of this program is teach the use of classes and functions, as well as program a rectangle validation program
*/

#ifndef RECTANGLE_HPP_INCLUDED
#define RECTANGLE_HPP_INCLUDED

#include "Point.hpp"

class Rectangle
{

private:
    Point p1, p2, p3, p4;
    bool sett(Point, Point, Point, Point);

public:
    Rectangle();
    Rectangle(Point, Point, Point, Point);
    float length();
    float width();
    float perimeter();
    float area();
    bool square();
    void setCoord(Point, Point, Point, Point);

};

#endif // RECTANGLE_HPP_INCLUDED
