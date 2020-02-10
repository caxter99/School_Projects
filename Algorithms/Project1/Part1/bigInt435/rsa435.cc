
// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

BigUnsigned createPrimeNumber(int numberOfDigits); // Takes the number of base 10 digits and generates a number that is extremely likely to be prime
bool testForPrimeStatus(BigUnsigned* num); // This function takes in a prime number and returns true if it is almost 100% likely to be prime, false otherwise
BigUnsigned* getBigger(BigUnsigned* num1, BigUnsigned* num2); // Returns a pointer to the larger big int number
BigUnsigned* getSmaller(BigUnsigned* num1, BigUnsigned* num2); // Returns a pointer to the smaller big int number
void writeAllToFiles(BigUnsigned* p, BigUnsigned* q, BigUnsigned* e, BigUnsigned* n, BigInteger* d); // Writes all of the integers to the file
unsigned long createLargeE(); // Creates a large intiger to act as the initial e value

// Global const variables
const int NUM_OF_DIGITS = 200; // Number of digits that will be in each big integer number (must be 155 or larger)
const int FERMANTS_FIRST_TEST = 2; // The first test using Fermant's Little Theorem will use this number
const int FERMANTS_SECOND_TEST = 3; // The second test using Fermant's Little Theorem will use this number
//const int INITIAL_E = 7; // The initial starting point for e (must be an odd number)
const unsigned long INITIAL_E = createLargeE(); // The initial starting point for e (must be an odd number)
const std::string PQ_FILENAME = "p_q.txt"; // The filename of the file that will store the integers p and q
const std::string EN_FILENAME = "e_n.txt"; // The filename of the file that will store the key(e, n)
const std::string DN_FILENAME = "d_n.txt"; // The filename of the file that will store the key(d, n)

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {
      // Making sure it's actually random
      srand(time(NULL));
		
      // Displaying that it's my project
      std::cout << "Devin Hopkins' Algorithms Project 1\n\n";

      // Creating and displaying p
      //
      //
      // Creating the first big integer (p)
      BigUnsigned p = createPrimeNumber(NUM_OF_DIGITS); // Correct
      //BigUnsigned p = BigUnsigned(11); // Testing
      // Displaying the first big integer
      std::cout << "First Bit Integer (p):\n";
      std::cout << p << "\n\n";

      // Creating and displaying q
      //
      //
      // Creating the second big integer (q)
      BigUnsigned q = createPrimeNumber(NUM_OF_DIGITS); // Correct
      //BigUnsigned q = BigUnsigned(13); // Testing
      // Displaying the second big number (q)
      std::cout << "Second Big Integer (q):\n";
      std::cout << q << "\n\n";
      
      // Creating and displaying n
      //
      //
      // Creating the third large integer (n)
      BigUnsigned n = p * q;
      // Displaying the third big integer (n)
      std::cout << "Third Big Integer (n):\n";
      std::cout << n << "\n\n";

      // Creating and displaying m (aka phi of n)
      //
      //
      // Creating the m (phi of n)
      BigUnsigned m = BigUnsigned(1);
      m = (p - 1) * (q - 1);
      // Displaying the fourth big integer (phi of n, m)
      std::cout << "Fourth Big Integer (phi of n, m):\n";
      std::cout << m << "\n\n";

      // Creating and displaying e, d, x, and y
      //
      //
      // Creating big integers x, y, and d are for the x value, y value, and gcd respectively
      BigInteger x, y, d;
      BigInteger correct = BigInteger(1);
      // Creating e, starting with the initial value minus 2 (since the first thing that happens after this is
      // that 2 is added to e, hence negating this minus 2)
      BigUnsigned e = BigUnsigned(INITIAL_E - 2);
      // Goes until the GCD of m and e is 1
      do {
         // Incrementing e by 2
         e = e + 2;
         // Using the Extended Euclidean Algorithm to find x, y, and d
         extendedEuclidean(m, e, d, x, y);
      }while(correct != d);
      // Displaying d
      std::cout << "Fifth Big Integer (d):\n";
      std::cout << d << "\n\n";
      // Displaying e
      std::cout << "Sixth Big Integer (e):\n";
      std::cout << e << "\n\n";
      // Displaying x
      std::cout << "Seventh Big Integer (x):\n";
      std::cout << x << "\n\n";
      // Displaying y
      std::cout << "Eighth Big Integer (y):\n";
      std::cout << y << "\n\n";

      std::cout << "Writing the integers to files..." << std::endl;
      writeAllToFiles(&p, &q, &e, &n, &y); // Writes all of the integers to the file (p, q, e, n, and d)
      std::cout << "Done writing the integers to files." << std::endl;

      //std::cout << "gcd(a, b) = x * a + y * b:\n" << d << " = " << x * m + y * e << std::endl;
      
	} catch(char const* err) {
      // Telling the user the library threw an exception
		std::cout << "The library threw an exception:\n" << err << "\n";
	}

   // Giving an extra line for the next command
   std::cout << "\n";

	return 0;
}

// Takes the number of base 10 digits and generates a number that is extremely likely to be prime
BigUnsigned createPrimeNumber(int numberOfDigits)
{
   // Creating the big integer (bigIntNum)
   BigUnsigned bigIntNum = BigUnsigned(1);

   // Puts 1 less than the total number of digits into the number
   for (int i = 0; i < numberOfDigits - 1; i++)
   {
      bigIntNum = bigIntNum * 10 + rand();
   }

   // The last number needs to be something that's not divisible by 2 or 5 so there's a better chance of it being prime
   int lastInt;
   do{
      lastInt = rand() % 10;
   }while(lastInt % 2 == 0 || lastInt == 5);

   // Adding the last digit to the number
   bigIntNum = bigIntNum * 10 + lastInt;

   // Testing to make sure it's prime
   if (testForPrimeStatus(&bigIntNum))
   {
      // If it is, return it
      return bigIntNum;
   }
   // If it's not prime, then a new big int must be created
   else
   {
      // Call the function again
      return createPrimeNumber(numberOfDigits);
   }
}

// This function takes in a prime number and returns true if it is almost 100% likely to be prime, false otherwise
bool testForPrimeStatus(BigUnsigned* num)
{
   // Creating necessary big unsigned integers
   BigUnsigned base1 = FERMANTS_FIRST_TEST; // Base for the first test
   BigUnsigned base2 = FERMANTS_SECOND_TEST; // Base for the second test
   BigUnsigned exponent = (*num) - 1; // The exponent for both tests
   BigUnsigned mod = (*num); // The mod for both tests
   BigUnsigned passes = BigUnsigned(1); // The number the result should return if the integers pass the test

   // This is the easy, non-special way
   return (passes == modexp(base1, exponent, mod) && passes == modexp(base2, exponent, mod));
}

// Returns a pointer to the larger big int number
BigUnsigned* getBigger(BigUnsigned* num1, BigUnsigned* num2)
{
   // The first number is larger than the second number
   if ((*num1) > (*num2))
   {
      // Return the first number
      return num1;
   }
   // The second number is larger than the first number (or they're equal)
   else
   {
      // Return the second number
      return num2;
   }
}

// Returns a pointer to the smaller big int number
BigUnsigned* getSmaller(BigUnsigned* num1, BigUnsigned* num2)
{
   // The first number is smaller than the second number
   if ((*num1) < (*num2))
   {
      // Return the first number
      return num1;
   }
   // The second number is smaller than the first number (or they're equal)
   else
   {
      // Return the second number
      return num2;
   }
}

// Writes all of the integers to the file
void writeAllToFiles(BigUnsigned* p, BigUnsigned* q, BigUnsigned* e, BigUnsigned* n, BigInteger* d)
{
   // Craeting the write file object
   std::ofstream writingObject;

   // Writing the p and q integers
   writingObject.open(PQ_FILENAME);
   if (writingObject)
   {
      writingObject << (*p) << "\n" << (*q);
   }
   else
   {
      std::cout << "could not write p and q to filename " << PQ_FILENAME << std::endl;
   }
   writingObject.close();

   // Writing the p and q integers
   writingObject.open(EN_FILENAME);
   if (writingObject)
   {
      writingObject << (*e) << "\n" << (*n);
   }
   else
   {
      std::cout << "could not write e and n to filename " << EN_FILENAME << std::endl;
   }
   writingObject.close();

   // Writing the p and q integers
   writingObject.open(DN_FILENAME);
   if (writingObject)
   {
      writingObject << (*d) << "\n" << (*n);
   }
   else
   {
      std::cout << "could not write d and n to filename " << DN_FILENAME << std::endl;
   }
   writingObject.close();
}

// Creates a large intiger to act as the initial e value
unsigned long createLargeE()
{
   // Initializing the temporary e (tempE)
   unsigned long tempE = 1;

   // Creating the limit for how many digits the tempE can be
   int limit = NUM_OF_DIGITS / 2;
   if (limit > 8)
   {
      limit = 8;
   }
   else if (limit <= 0)
   {
      limit = 1;
   }

   // Looping through and making e as big as possible
   for (int x = 0; x < limit; ++x)
   {
      tempE = tempE * 10 + rand() % 10;
   }

   // Making sure the last digit is an odd digit
   int lastInt;
   do{
      lastInt = rand() % 10;
   }while(lastInt % 2 == 0);

   // Adding the last digit to the number
   tempE = tempE * 10 + lastInt;

   // Returning the e value
   return tempE;
}
















