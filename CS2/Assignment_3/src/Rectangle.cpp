/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 3
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.12.2018
Purpose: The purpose of this program is teach the use of classes and functions, as well as program a rectangle validation program
*/

// Importing all necessary libraries and files
#include "Rectangle.hpp"
#include <math.h>

// Default constructor
Rectangle::Rectangle()
{
    Point p1{0.0, 0.0};
    Point p2{0.0, 1.0};
    Point p3{1.0, 0.0};
    Point p4{1.0, 1.0};
}

// This constructor expects four Point objects as arguments
Rectangle::Rectangle(Point one, Point two, Point three, Point four)
{
    // If the Point objects are good, then the rectangle is initiated using the four Point objects
    if (sett(one, two, three, four))
    {
        p1 = one;
        p2 = two;
        p3 = three;
        p4 = four;
    }
    // If they don't, then a set of pre-made Point objects are used
    else
    {
        Point p1{0.0, 0.0};
        Point p2{0.0, 1.0};
        Point p3{1.0, 0.0};
        Point p4{1.0, 1.0};
    }
}

// PRE: Expects four Point objects
// POST: Will return true if the four Point objects make a rectangle and fit the limits given, will return false otherwise
bool Rectangle::sett(Point one, Point two, Point three, Point four)
{
    // Checking to see if the first coordinate is in Q1 and within the respective limits of 0 and 20
    if (one.getX() >= 0 && one.getX() <= 20 && one.getY() >= 0 && one.getY() <= 20)
    {
        // Checking to see if the second coordinate is in Q1 and within the respective limits of 0 and 20
        if (two.getX() >= 0 && two.getX() <= 20 && two.getY() >= 0 && two.getY() <= 20)
        {
            // Checking to see if the third coordinate is in Q1 and within the respective limits of 0 and 20
            if (three.getX() >= 0 && three.getX() <= 20 && three.getY() >= 0 && three.getY() <= 20)
            {
                // Checking to see if the fourth coordinate is in Q1 and within the respective limits of 0 and 20
                if (four.getX() >= 0 && four.getX() <= 20 && four.getY() >= 0 && four.getY() <= 20)
                {
                    // This gets the length of each side
                    float sideTop = sqrt(pow(one.getX() - two.getX(), 2) + pow(one.getY() - two.getY(), 2));
                    float sideRight = sqrt(pow(three.getX() - two.getX(), 2) + pow(three.getY() - two.getY(), 2));
                    float sideBottom = sqrt(pow(three.getX() - four.getX(), 2) + pow(three.getY() - four.getY(), 2));
                    float sideLeft = sqrt(pow(one.getX() - four.getX(), 2) + pow(one.getY() - four.getY(), 2));

                    // Checking to see if the four points actually make a rectangle
                    if (sideTop == sideBottom && sideRight == sideLeft)
                    {
                        // If everything checks out, true is returned
                        return true;
                    }
                }
            }
        }
    }
    // If anyone of those tests fails, false is returned to indicate the fours points don't meet the requirements
    return false;
}

// PRE: None
// POST: Returns the length of a rectangle
float Rectangle::length()
{
    // Makes the first point's coordinates the distance from which everything is measured from
    float baseX = p1.getX();
    float baseY = p1.getY();

    // Getting the length to every other point
    float sideOne = sqrt(pow(baseX - p2.getX(), 2) + pow(baseY - p2.getY(), 2));
    float sideTwo = sqrt(pow(baseX - p3.getX(), 2) + pow(baseY - p3.getY(), 2));
    float sideThree = sqrt(pow(baseX - p4.getX(), 2) + pow(baseY - p4.getY(), 2));

    // This tries to find the second longest distance, which will be the longest length, and return it
    if (sideOne > sideTwo && sideTwo > sideThree)
    {
        return sideTwo;
    }
    else if(sideTwo > sideOne && sideOne > sideThree)
    {
        return sideOne;
    }
    else
    {
        return sideThree;
    }
}

// PRE: None
// POST: Returns the width of the rectangle
float Rectangle::width()
{
    // Makes the first point's coordinates the distance from which everything is measured from
    float baseX = p1.getX();
    float baseY = p1.getY();

    // Getting the length to every other point
    float sideOne = sqrt(pow(baseX - p2.getX(), 2) + pow(baseY - p2.getY(), 2));
    float sideTwo = sqrt(pow(baseX - p3.getX(), 2) + pow(baseY - p3.getY(), 2));
    float sideThree = sqrt(pow(baseX - p4.getX(), 2) + pow(baseY - p4.getY(), 2));

    // This tries to find the shortest length and return it
    if (sideOne > sideThree && sideTwo > sideThree)
    {
        return sideThree;
    }
    else if(sideOne > sideTwo && sideThree > sideTwo)
    {
        return sideTwo;
    }
    else
    {
        return sideOne;
    }
}

// PRE: None
// POST: Returns the area of the rectangle
float Rectangle::area()
{
    return length() * width();
}

// PRE: None
// POST: Returns the perimeter of the rectangle
float Rectangle::perimeter()
{
    return 2 * (length() + width());
}

// PRE: None
// POST: Returns true if the rectangle is a square and false if it's not
bool Rectangle::square()
{
    // Sees if the shorter side equals the longer side to see if the rectangle is a square
    if (length() == width())
    {
        return true;
    }
    return false;
}
