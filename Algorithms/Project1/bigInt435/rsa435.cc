// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// This function validates d
bool validD(BigUnsigned* d, BigUnsigned* m, int e);

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {

      // NOTES: The instructions say that the size of our digits must be at least 512 bits. This is equivalent to having 155 (base 10) digits.

      // Number of digits that will be in each number
      const int NUM_OF_DIGITS = 400;

      // Making sure it's actually random
      srand(time(NULL));
		
      // Displaying that it's my project
      std::cout << "Devin Hopkins' Algorithms Project 1\n\n";

      // Creating the first big integer (p)
      BigUnsigned p = BigUnsigned(1);

      // Puts 1 less than the total number of digits into the number
      for (int i = 0; i < NUM_OF_DIGITS - 1; i++)
      {
         p = p * 10 + rand();
      }

      // The last number needs to be something that's not divisible by 2 so there's a better chance of it being prime
      int lastInt;
      do{
         lastInt = rand() % 10;
      }while(lastInt % 2 == 0 || lastInt == 5);

      // Adding the last digit to the number
      p = p * 10 + lastInt;

      // Displaying the firs tbig integer
      std::cout << "First Bit Integer (p):\n";
      std::cout << p << "\n\n";

      // Creating the second big integer (q)
      BigUnsigned q = BigUnsigned(1);

      // Puts 1 less than the total number of digits into the number
      for (int i = 0; i < NUM_OF_DIGITS - 1; i++)
      {
         q = q * 10 + rand();
      }

      // The last number needs to be something that's not divisible by 2 so there's a better chance of it being prime
      do{
         lastInt = rand() % 10;
      }while(lastInt % 2 == 0 || lastInt == 5);

      // Adding the last digit to the number
      q = q * 10 + lastInt;

      // Displaying the second big number
      std::cout << "Second Big Integer (q):\n";
      std::cout << q << "\n\n";
      
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

// This function validates d
bool validD(BigUnsigned* d, BigUnsigned* m, int e)
{
   return true; // Temporary
   //return (((*d) * e) % (*m)) == 1; // This is the legit one, I believe
}





