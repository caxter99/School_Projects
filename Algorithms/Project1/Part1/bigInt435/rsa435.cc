
// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

BigUnsigned createPrimeNumber(int numberOfDigits); // Takes the number of base 10 digits and generates a number that is extremely likely to be prime
bool testForPrimeStatus(BigUnsigned* num); // This function takes in a prime number and returns true if it is almost 100% likely to be prime, false otherwise
void writeAllToFiles(BigUnsigned* p, BigUnsigned* q, BigUnsigned* e, BigUnsigned* n, BigUnsigned* d); // Writes all of the integers to the file
unsigned long createInitialE(); // Creates a large integer to act as the initial e value
BigUnsigned createE(BigUnsigned m); // Creates a big unsigned e based on the big unsigned sent in
BigInteger createX(BigUnsigned m, BigUnsigned e); // Returns a big unsigned x (assumes a correct e value)

// Global const variables
const bool SHOW_RESULTS = true; // If true, shows the results of every number that gets created (includes the tests)
const bool SHOW_TESTS = true; // If true (along with SHOW_RESULTS), the tests will be displayed
const int NUM_OF_DIGITS = 200; // Number of digits that will be in each big integer number (must be 155 or larger)
const int FERMANTS_FIRST_TEST = 2; // The first test using Fermant's Little Theorem will use this number
const int FERMANTS_SECOND_TEST = 3; // The second test using Fermant's Little Theorem will use this number
const unsigned long INITIAL_E = createInitialE(); // The initial starting point for e (must be an odd number)
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
		
      // Displaying that it's my project and that creating the integers has started
      std::cout << "\nDevin Hopkins' Algorithms Project 1\nCreating all necessary integers...\n";

      // Creating p
      BigUnsigned p = createPrimeNumber(NUM_OF_DIGITS);

      // Creating q
      BigUnsigned q = createPrimeNumber(NUM_OF_DIGITS);

      // Creating n
      BigUnsigned n = p * q;

      // Creating phi of n (stored in variable m)
      BigUnsigned m = (p - 1) * (q - 1);

      // Creating e
      BigUnsigned e = createE(m);

      // Creating d
      BigUnsigned d = modinv(e, m);

      // Letting the user know all of the integers have been created
      std::cout << "All of the integers have been created.\n";
      
      // Writes all of the integers to the file (p, q, e, n, and d)
      writeAllToFiles(&p, &q, &e, &n, &d);

      // Chcking to see if they are to be displayed
      if (SHOW_RESULTS)
      {
         // Letting the user know they're about to see all of the results
         std::cout << "Displaying all of the integers:\n";

         // Displaying p
         std::cout << "p:\n";
         std::cout << p << "\n\n";

         // Displaying q
         std::cout << "q:\n";
         std::cout << q << "\n\n";

         // Displaying n
         std::cout << "n:\n";
         std::cout << n << "\n\n";

         // Displaying phi of n (stored in variable m)
         std::cout << "phi of n:\n";
         std::cout << m << "\n\n";

         // Displaying e
         std::cout << "e:\n";
         std::cout << e << "\n\n";

         // Displaying d
         std::cout << "d:\n";
         std::cout << d << "\n\n";

         // Checking to see if the user wants to see the tests
         if (SHOW_TESTS)
         {
            // Telling the user about the tests
            std::cout << "Tests:\n";

            // First test
            std::cout << "Test #1: (e * d) % phi of n = 1\n";
            std::cout << "                          " << (e * d) % m << " = 1\n\n";

            // Second test
            //std::cout << "Test #2: (x * phi of n) + d * e = 1\n";
            //std::cout << "                              " << (createX(m, e) * m) + (d * e) << " = 1\n\n";
         }
      }      
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

// Writes all of the integers to the file
void writeAllToFiles(BigUnsigned* p, BigUnsigned* q, BigUnsigned* e, BigUnsigned* n, BigUnsigned* d)
{
   // Letting the user know that the integers are being written to the file
   std::cout << "Writing the integers to files..." << std::endl;

   // Creating the write file object
   std::ofstream writingObject;

   // Writing the p and q integers
   writingObject.open(PQ_FILENAME);
   if (writingObject)
   {
      writingObject << (*p) << "\n" << (*q);
   }
   else
   {
      std::cout << "Could not write p and q to filename " << PQ_FILENAME << std::endl;
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
      std::cout << "Could not write e and n to filename " << EN_FILENAME << std::endl;
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
      std::cout << "Could not write d and n to filename " << DN_FILENAME << std::endl;
   }
   writingObject.close();

   // Letting the user know that everything has been written
   std::cout << "Done writing the integers to files." << std::endl;
}

// Creates a large integer to act as the initial e value
unsigned long createInitialE()
{
   // Initializing the temporary e (tempE)
   unsigned long tempE = 1;

   // Creating the limit for how many digits the tempE can be
   int limit = NUM_OF_DIGITS / 2;
   if (limit > 7)
   {
      limit = 7;
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

// Creates a big unsigned e based on the big unsigned sent in
BigUnsigned createE(BigUnsigned m)
{
   // Creating everything necessary to find e
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

   // Return e
   return e;
}

// Returns a big integer x (assumes a correct e value)
BigInteger createX(BigUnsigned m, BigUnsigned e)
{
   // Creating all the variables necessary for the Extended Euclidean Algorithm
   BigInteger x, y, d;

   // Running the Extended Euclidean Algorithm
   extendedEuclidean(m, e, d, x, y);

   // Returning x
   return x;
}

















