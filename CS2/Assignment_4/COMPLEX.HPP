/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 4
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.8.2018
Purpose: This program is the test cases for the assignment
*/

#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <string>

class Complex
{
public:
   Complex(double = 0.0, double = 0.0); // default constructor
   Complex operator+(const Complex&) const; // function add
   Complex operator-(const Complex&) const; // function subtract
   Complex operator*(const Complex&) const; // function multiply
   void setComplexNumber(double, double); // set complex number
   friend std::istream& operator>> (std::istream&, Complex&); // function input
   friend std::ostream& operator<< (std::ostream&, Complex&); // function output
   bool operator!=(const Complex&) const; // function is not equal
   bool operator==(const Complex&) const; // function is equal

private:
   double realPart;
   double imaginaryPart;
};

#endif

