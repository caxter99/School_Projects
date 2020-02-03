// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

bool validD(BigUnsigned* d, BigUnsigned* m, int e); // Returns true if d is valid
BigUnsigned createPrimeNumber(int numberOfDigits); // Takes the number of base 10 digits and generates a number that is extremely likely to be prime
bool testForPrimeStatus(BigUnsigned* num); // This function takes in a prime number and returns true if it is almost 100% likely to be prime, false otherwise

// Global const variables
const int NUM_OF_DIGITS = 155; // Number of digits that will be in each big integer number (we just need 155)
const int FERMANTS_FIRST_TEST = 2; // The first test using Fermant's Little Theorem will use this number
const int FERMANTS_SECOND_TEST = 3; // The second test using Fermant's Little Theorem will use this number

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {

      // NOTES: The instructions say that the size of our digits must be at least 512 bits. This is equivalent to having 155 (base 10) digits.

      // Making sure it's actually random
      srand(time(NULL));
		
      // Displaying that it's my project
      std::cout << "Devin Hopkins' Algorithms Project 1\n\n";

      // Creating the first big integer (p)
      BigUnsigned p = createPrimeNumber(NUM_OF_DIGITS);

      // Displaying the firs tbig integer
      std::cout << "First Bit Integer (p):\n";
      std::cout << p << "\n\n";

      // Creating the second big integer (q)
      BigUnsigned q = createPrimeNumber(NUM_OF_DIGITS);

      // Displaying the second big number
      std::cout << "Second Big Integer (q):\n";
      std::cout << q << "\n\n";

      // ANYTHING AFTER THIS PART IN MAIN STILL MUST BE MODIFIED.
      // WE HAVEN'T GONE OVER THE NEXT PART IN CLASS SO I'M STILL UNSURE
      // HOW TO DO IT. KEEP THAT IN MIND PLEASE.
      
      // Creating the third large integer (n)
      BigUnsigned n = BigUnsigned(1);
      n = p * q;

      // Displaying the third big integer (n)
      std::cout << "Third Big Integer (n):\n";
      std::cout << n << "\n\n";

      // Creating the omega n thing
      BigUnsigned m = BigUnsigned(1);
      m = (p - 1) * (q - 1);

      // Displaying the fourth big integer (m)
      std::cout << "Fourth Big Integer (m):\n";
      std::cout << m << "\n\n";

      // Picking e
      int e = 7;
      do{
         ++e;
      //}while((n % e) == 0 && (m % e) == 0); // This tests e against n and m
      }while((m % e) == 0); // This tests e against m

      // Dislpaying e
      std::cout << "Regular Integer (e):\n";
      std::cout << e << "\n\n";

      // Finding d
      BigUnsigned d = BigUnsigned(1);
      d = 1;
      while(!validD(&d, &m, e))
      {
         d++;
      }

      // Displaying the fifth big integer (d)
      std::cout << "Fifth Big Integer (d):\n";
      std::cout << d << "\n\n";
      
	} catch(char const* err) {
      // Telling the user the library threw an exception
		std::cout << "The library threw an exception:\n" << err << "\n";
	}

   // Giving an extra line for the next command
   std::cout << "\n";

	return 0;
}

// Returns true if d is valid
bool validD(BigUnsigned* d, BigUnsigned* m, int e)
{
   return true; // Temporary
   //return (((*d) * e) % (*m)) == 1; // This is the legit one, I believe
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

      // The last number needs to be something that's not divisible by 2 so there's a better chance of it being prime
      int lastInt;
      do{
         lastInt = rand() % 10;
      }while(lastInt % 2 == 0 || lastInt == 5);

      // Adding the last digit to the number
      bigIntNum = bigIntNum * 10 + lastInt;

      // Testing to make sure it's prime
      if (testForPrimeStatus(&bigIntNum))
      {
         return bigIntNum;
      }
      // If it's not prime, then a new big int must be created
      else
      {
         return createPrimeNumber(numberOfDigits);
      }
}

// This function takes in a prime number and returns true if it is almost 100% likely to be prime, false otherwise
bool testForPrimeStatus(BigUnsigned* num)
{
   //Creating necessary big unsigned integers
   BigUnsigned base1 = FERMANTS_FIRST_TEST; // Base for the first test
   BigUnsigned base2 = FERMANTS_SECOND_TEST; // Base for the second test
   BigUnsigned exponent = (*num) - 1; // The exponent for both tests
   BigUnsigned mod = (*num); // The mod for both tests
   BigUnsigned passes = 1; // The number the result should return if the integers pass the test

   // This is the easy, non-special way
   return (passes == modexp(base1, exponent, mod) && passes == modexp(base2, exponent, mod));
}


