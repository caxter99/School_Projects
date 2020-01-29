/*
COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
CSI Project 1
Author: Devin Hopkins
	djh155@zips.uakron.edu
Version: 1.01 2.28.2018
Purpose: This program to demonstrate all the knowledge we have learned in this course thus far.
*/

#include "rational.hpp"

// PRE: This constructor takes two int arguments and, after reducing them, assigns them to the fraction
// POST: The numerator and the denominator are set
Rational::Rational(int top, int bottom)
{
    // Making sure the user didn't enter in 0 for the denominator. If they did, make it 1
    if (bottom == 0)
    {
        bottom = 1;
    }

    // Figuring out if the two numbers entered can be reduced by finding their gcd
    int gcdNum = gcd(top, bottom);

    // If they can be reduced, the code goes in here and reduces them, then assigns them to the appropriate variable
    if (gcdNum != 1)
    {
        n = top / gcdNum;
        d = bottom / gcdNum;
    }

    // If they can't be reduced, the code goes in here and assigns them to the appropriate variable
    else
    {
        n = top;
        d = bottom;
    }
}
Rational::~Rational()
{
    //dtor
}

// PRE: Expects a Rational object
// POST: Returns true if the two objects are equal to each other, false otherwise
bool Rational::operator== (const Rational& right)
{
    return ((n == right.n && d == right.d) || (n == 0 && right.n == 0));
}

// PRE: Expects a Rational object
// POST: Returns true if the two objects are equal to each other, false otherwise
bool Rational::operator!= (const Rational& right)
{
    return ((n != right.n && d == right.d) || (n == right.n && d != right.d));
}

// PRE: Expects a Rational object
// POST: Returns true if the Rational object on the left is greater than the Rational object on the right
bool Rational::operator> (const Rational& right)
{
    return (((float)n) / d > ((float)right.n) / right.d);
}

// PRE: Expects a Rational object
// POST: Returns true if the Rational object on the left is less than the Rational object ton the right
bool Rational::operator< (const Rational& right)
{
    return (((float)n) / d < ((float)right.n) / right.d);
}

// PRE: Expects a Rational object
// POST: Returns true if the Rational object on the left is greater than the Rational object on the right or
//       they are equal
bool Rational::operator<= (const Rational& right)
{
    return (((float)n) / d <= ((float)right.n) / right.d);
}

// PRE: Expects a Rational object
// POST: Returns true if the Rational object on the left is less than the Rational object on the right or
//       they are equal
bool Rational::operator>= (const Rational& right)
{
    return (((float)n) / d >= ((float)right.n) / right.d);
}

// PRE: Expects a Rational object
// POST: Returns a Rational object that is the additional of the two Rational objects
Rational Rational::operator+ (const Rational& right)
{
    return Rational(n * right.d + right.n * d, d * right.d);
}

// PRE: Expects a Rational object
// POST: Returns a Rational object that returns the left Rational object minus the first Rational object
Rational Rational::operator- (const Rational& right)
{
    return Rational(n * right.d - right.n * d, d * right.d);
}

// PRE: Expects a Rational object
// POST: Returns a Rational object that is the product of the left and right Rational objects
Rational Rational::operator* (const Rational& right)
{
    return Rational(n * right.n, d * right.d);
}

// PRE: Expects a Rational object
// POST: Returns a Rational object that contains the number of the left Rational object divided by the right
//       Rational object
Rational Rational::operator/ (const Rational& right)
{
    return Rational(n * right.d, d * right.n);
}

// This starts the integer on the right overloading

// PRE: Expects an integer
// POST: Returns true of the integer is equal to the Rational object, returns false otherwise
bool Rational::operator== (int number)
{
    return (((float)n) / d == number);
}

// PRE: Expects an integer
// POST: Returns true of the integer is not equal to the Rational object, returns false otherwise
bool Rational::operator!= (int number)
{
    return (!(((float)n) / d == number));
}

// PRE: Expects an integer
// POST: Returns true of the integer is less than the Rational object, returns false otherwise
bool Rational::operator> (int number)
{
    return (((float)n) / d > number);
}

// PRE: Expects an integer
// POST: Returns true of the integer is greater than the Rational object, returns false otherwise
bool Rational::operator< (int number)
{
    return (((float)n) / d < number);
}

// PRE: Expects an integer
// POST: Returns true of the integer is greater than or equal to than the Rational object, returns false otherwise
bool Rational::operator<= (int number)
{
    return (((float)n) / d <= number);
}

// PRE: Expects an integer
// POST: Returns true of the integer is less than or equal to the Rational object, returns false otherwise
bool Rational::operator>= (int number)
{
    return (((float)n) / d >= number);
}

// PRE: Expects an integer
// POST: Returns a Rational object that contains the sum of the integer and the Rational object
Rational Rational::operator+ (int number)
{
    number *= d;
    return Rational(number + n, d);
}

// PRE: Expects an integer
// POST: Returns a Rational object that contains the difference of the Rational object and the integer
Rational Rational::operator- (int number)
{
    number *= d;
    return Rational(n - number, d);
}

// PRE: Expects an integer
// POST: Returns a Rational object that contains the product of the integer and the Rational object
Rational Rational::operator* (int number)
{
    return Rational(number * n, d);
}

// PRE: Expects an integer
// POST: Returns a Rational object that contains the quotient of the Rational object and the integer
Rational Rational::operator/ (int number)
{
    return Rational(n, d * number);
}

// This end the integer on the right overloading

// This begins the integer on the left overloading

// PRE: Expects an integer and a Rational object
// POST: Returns true if the integer and the Rational object are equal, returns false otherwise
bool operator== (int number, Rational& right)
{
    return (((float)right.n) / right.d == number);
}

// PRE: Expects an integer and a Rational object
// POST: Returns true if the integer does not equal the Rational object, returns false otherwise
bool operator!= (int number, Rational& right)
{
    return (!(((float)right.n) / right.d == number));
}

// PRE: Expects an integer and a Rational object
// POST: Returns true if the integer is greater than the Rational object, returns false otherwise
bool operator> (int number, Rational& right)
{
    return (number > ((float)right.n) / right.d);
}

// PRE: Expects an integer and a Rational object
// POST: Returns true if the integer is less than the Rational object, returns false otherwise
bool operator< (int number, Rational& right)
{
    return (number < ((float)right.n) / right.d);
}

// PRE: Expects an integer and a Rational object
// POST: Returns true if the integer is less than or equal to the Rational object, returns false otherwise
bool operator<= (int number, Rational& right)
{
    return (number <= ((float)right.n) / right.d);
}

// PRE: Expects an integer and a Rational object
// POST: Returns true if the integer is greater than or equal to the Rational object, returns false otherwise
bool operator>= (int number, Rational& right)
{
    return (number >= ((float)right.n) / right.d);
}

// PRE: Expects an integer and a Rational object
// POST: Returns a Rational object containing the integer plus the Rational object
Rational operator+ (int number, Rational& right)
{
    number *= right.d;
    return Rational(number + right.n, right.d);
}

// PRE: Expects an integer and a Rational object
// POST: Returns a Rational object containing the integer minus the Rational object
Rational operator- (int number, Rational& right)
{
    number *= right.d;
    return Rational(number - right.n, right.d);
}

// PRE: Expects an integer and a Rational object
// POST: Returns a Rational object containing the product of the integer and the Rational object
Rational operator* (int number, Rational& right)
{
    return Rational(number * right.n, right.d);
}

// PRE: Expects an integer and a Rational object
// POST: Returns a Rational object containing the integer divided by the Rational object
Rational operator/ (int number, Rational& right)
{
    return Rational(number * right.d, right.n);
}

// This ends the integer on the left overloading

// -------------------------------------------------------------------------- //
// Helper functions

// Compute the GCD (greatest common divider) of two integer values using Euclid's algorithm.
int Rational::gcd(int a, int b)
{
  a = abs(a);   //make them to be positive numbers
  b = abs(b);
  if(a==0 || b==0){ //if one number is 0, always return 1
    return 1;
  }
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}


// Compute the LCM (Least Common Multiple) of two integer values.
int Rational::lcm(int a, int b)
{
  a = abs(a); //make them positive
  b = abs(b);
  if(a == 0 || b == 0){
    throw "Integers can not be zero in calculating Least Common Multiple";
  }
  return (abs(a) / gcd(a, b)) * abs(b);
}


// -------------------------------------------------------------------------- //
// Rational implementation


//DO NOT CHANGE operators << and >> overloading functions
std::ostream& operator<<(std::ostream& os, Rational r)
{
    // The prompt said we could modify these functions, so I did. My modifications start here
    if (r.den() == 1 && r.num() != 0)
    {
        return os << r.num();
    }
    // My modifications end here

    return os << r.num() << '/' << r.den();
}

std::istream& operator>>(std::istream& is, Rational& r)
{
  // Read the first integer, return on error.
  int p;
  is >> p;
  if (!is)
    return is;

  // Check for the divider. Assuming no spaces.
  if (is.peek() != '/') {
    r = Rational(p);
    return is;
  }
  is.get();

  int q;
  is >> q;
  if (!is)
    return is;
  if (q == 0) {
    is.setstate(std::ios::failbit);
    return is;
  }
  r = Rational(p, q);
  return is;
#if 0
  int p, q;
  char c;
  is >> p >> c >> q;
  if (!is)
    return is;
  // Require that the divider to be a '/'.
  if (c != '/') {
    is.setstate(std::ios::failbit);
    return is;
  }

  // Make sure that we didn't read p/0.

  r = Rational(p, q);
  return is;
#endif
}
