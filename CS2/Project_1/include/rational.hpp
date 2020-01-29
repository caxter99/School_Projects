/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 1
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.28.2018
Purpose: This program to demonstrate all the knowledge we have learned in this course thus far.
*/

// COPYRIGHT (C) 2017 Student Name (UANET ID ) All rights reserved.
//
// rational.hpp: Definition of rational class and its interace.

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <stdlib.h>

/* Not sure if I can move these into the class????? I did anyway.
// Mathematical helper functions.
//
// NOTE: These are defined in rational.cpp.
int gcd(int, int);
int lcm(int, int);
*/


// Represents a rational number. The rational numbers are the set of
// numbers that can be represented as the quotient of two integers.
class Rational
{
  // TODO: Define the following:
  // 1. A default constructor
  // 2. A constructor that takes an integer value
  // 3. A constructor that takes a pair of values

  public:
      // Constructors
      Rational() { n = 0; d = 1; };
      Rational(int top) { n = top; d = 1; };
      Rational(int, int);

      // When comparing two Rational objects
      bool operator== (const Rational&);
      bool operator!= (const Rational&);
      bool operator> (const Rational&);
      bool operator< (const Rational&);
      bool operator<= (const Rational&);
      bool operator>= (const Rational&);
      Rational operator+ (const Rational&);
      Rational operator- (const Rational&);
      Rational operator* (const Rational&);
      Rational operator/ (const Rational&);

      // When comparing a Rational object and an integer, with the integer on the right
      bool operator== (int);
      bool operator!= (int);
      bool operator> (int);
      bool operator< (int);
      bool operator<= (int);
      bool operator>= (int);
      Rational operator+ (int);
      Rational operator- (int);
      Rational operator* (int);
      Rational operator/ (int);

      // When comparing a Rational object and an integer, with the integer on the left
      friend bool operator== (int, Rational&);
      friend bool operator!= (int, Rational&);
      friend bool operator> (int, Rational&);
      friend bool operator< (int, Rational&);
      friend bool operator<= (int, Rational&);
      friend bool operator>= (int, Rational&);
      friend Rational operator+ (int, Rational&);
      friend Rational operator- (int, Rational&);
      friend Rational operator* (int, Rational&);
      friend Rational operator/ (int, Rational&);

      // Destructor, input, and output methods
      virtual ~Rational();
      friend std::ostream& operator<<(std::ostream&, Rational);
      friend std::istream& operator>>(std::istream&, Rational&);

      // Returns the numerator.
      int num() const { return n; };

      // Returns the denominator
      int den() const { return d; };

  private:
    int n, d;
    int gcd(int, int);
    int lcm(int, int);

};


// TODO: Implement support for
// 1. Comparing two rational numbers for equality:
//    - r1 == t2
//    - r1 != r2
// 2. Ordering rational numbers
//    - r1 < r2
//    - r1 > r2
//    - r1 <= r2
//    - r1 >= r2
// 3. The standard arithmetic operators
//    - r1 + r2
//    - r1 - r2
//    - r1 * r2
//    - r1 / r2

#endif
