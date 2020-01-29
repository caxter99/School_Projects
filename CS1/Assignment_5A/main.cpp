/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 5A
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 10.09.2017
Purpose: This program checks and sees if the entered number is prime. It also will output
         all numbers from 2 to the entered number that are prime.
*/

// Importing the io stream
#include <iostream>

// Importing necessary standard functions
using std::cout;
using std::cin;
using std::endl;
using std::string;

// This function will return true if the number is prime and false if it is not prime
bool isPrime(int);

// This function will output all the prime numbers from 2 to the int
void printAllPrime(int);

int main()
{
    // Declaring my variables
    int number = 0;
    string goOn = "";

    // A do while loop, in case they want to test multiple numbers
    do
    {
       // Asking for input
       cout << "Enter a number to see if it's prime: ";
       cin >> number;

       // Verifying that the input is correct
       do
       {
          if (cin.fail() || number < 0)
          {
             cin.clear();
             cin.ignore(1000, '\n');
             cout << endl << "That was not a valid answer. Try again." << endl;
             cout << "Enter a number to see if it's prime: ";
             cin >> number;
          }
       }while(cin.fail() || number < 0);

       // Making my output look nicer
       cout << endl;

       // Outputting all the prime numbers from 2 to the entered number
       printAllPrime(number);

       // Checking to see if the entered number is prime and outputting the correct result
       if (isPrime(number))
       {
          cout << number << " is prime!" << endl;
       }
       else
       {
          cout << number << " is not prime." << endl;
       }

       // Asking if the user wants to test another number
       cout << endl << "Would you like to test another number? (y or n)" << endl;
       cin >> goOn;
       cout << endl;

    }while(goOn == "y" || goOn == "Y");

    return 0;
}

// This function will return true if the number is prime and false if it is not prime
bool isPrime(int num)
{
   // Tests to see if the number is divisible by any other number, thus testing if it's prime or not
   for (int x = 2; x < num; x++)
   {
      if (num % x == 0)
      {
         return false;
      }
   }
   return true;
}

// This function will output all the prime numbers from 2 to the int
void printAllPrime(int num)
{
   // If the number is 2, this function will automatically quit
   if (num == 2)
   {
      return;
   }

   // Declaring my variable
   bool isAPrimeNum = true;

   // Finding and printing all the prime numbers
   for (int x = 2; x < num; x++)
   {
      isAPrimeNum = true;
      for (int y = 2; y < x; y++)
      {
         if (x % y == 0)
         {
            isAPrimeNum = false;
         }
      }
      if (isAPrimeNum)
      {
         cout << " " << x;
      }
   }

   // Letting the user know what the list of numbers means
   cout << endl;
   cout << "The previous list are all prime numbers from 0 to " << num << "." << endl;
}
