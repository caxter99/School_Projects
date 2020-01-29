/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 4
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.8.2018
Purpose: This program is the test cases for the assignment
*/

// Member-function definitions for class Complex.
#include <iostream>
#include <sstream> // for ostringstream class
#include "Complex.hpp"

// Default constructor that also can take one or two parameters
Complex::Complex(double real, double imaginary)
   : realPart(real), imaginaryPart(imaginary) { }


// PRE: Expects one Complex object
// POST: Returns a Complex object with the complex numbers of both the first and second object added together
Complex Complex::operator+(const Complex &right) const
{
   return Complex(realPart + right.realPart, imaginaryPart + right.imaginaryPart);
}

// PRE: Expects one Complex object
// POST: Returns a Complex object with the complex numbers of the first object minus the second object
Complex Complex::operator-(const Complex &right) const
{
   return Complex(realPart - right.realPart, imaginaryPart - right.imaginaryPart);
}

// PRE: Expects one Complex object
// POST: Returns a Complex object with the two complex numbers multiplied together
Complex Complex::operator*(const Complex &right) const
{
   return Complex((realPart * right.realPart), (imaginaryPart * right.imaginaryPart));
}

// PRE: Expects to overload the cin operator >> and also takes one Complex object
// POST: Returns the cin operator >>, but also grabs the complex number from the user
std::istream& operator>> (std::istream &in, Complex &right)
{
    // Getting the real part of the complex number
    std::string tempString = "";
    getline(in, tempString, '(');
    in >> right.realPart;

    // Getting the unreal part of the complex number
    getline(in, tempString, ',');
    in >> right.imaginaryPart;
    return in;
}

// PRE: Expects to overload the cout operator << and also takes one Complex object
// POST: Returns the cout operator <<, but also prints out the complex number from the user
std::ostream& operator<< (std::ostream &out, Complex& right)
{
    std::cout << "(" << right.realPart << " + " << right.imaginaryPart << "*i)";
    return out;
}

// PRE: Expects one Complex object
// POST: Returns a Complex object with the two complex numbers multiplied together
bool Complex::operator!=(const Complex &right) const
{
    if (right.realPart == realPart && right.imaginaryPart == imaginaryPart)
    {
        return false;
    }
    return true;
}

// PRE: Expects one Complex object
// POST: Returns true if the two Complex objects (numbers) are equal to each other and false otherwise
bool Complex::operator==(const Complex &right) const
{
    // Checks to make sure both the real and the imaginary part of the complex number are equal
    if (right.realPart == realPart && right.imaginaryPart == imaginaryPart)
    {
        return true;
    }
    return false;
}
