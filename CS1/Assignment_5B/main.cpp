/*
COPYRIGHT (C) 2017 Devin Hopkins (4190350) All rights reserved.
CSI Assignment 5A
Author: Devin Hopkins
        djh155@zips.uakron.edu
Version: 1.01 10.09.2017
Purpose: This program determines the ultimate dodge ball player.
*/

// Importing necessary libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Importing necessary std library function
using std::cout;
using std::cin;
using std::endl;
using std::showpoint;
using std::setprecision;

// This function returns if the person getting shot at gets hit or not
void shoot(bool&, double);

// This function starts the duel and returns the winner
int startDuel();

// This function returns true if there is only one person left alive
bool isOneAlive(bool, bool, bool);

int main()
{
   // Declaring constants and variables
   const int NUMDUELS = 1000;
   int winner;
   int aaronWins = 0;
   int bobWins = 0;
   int charlieWins = 0;

   // Making sure every time I call rand() it's something different
   srand(time(0));

   // This loop runs the duel 1,000 times to make sure we get the best results
   for (int x = 0; x < NUMDUELS; x++)
   {
      // The winner is returned in the form of an integer
      winner = startDuel();

      // Making sure the winner gets credit for their win
      if (winner == 0)
      {
         aaronWins++;
      }
      else if (winner == 1)
      {
         bobWins++;
      }
      else
      {
         charlieWins++;
      }
   }

   // Making sure all of my number outputs look nice
   cout << showpoint << setprecision(3) << endl;

   // Outputting the results
   cout << "After playing 1,000 games the results are in!\nAaron also intentionally missed his first shot." << endl;
   cout << endl << "  Aaron Win %: " << float(aaronWins) / NUMDUELS * 100 << endl;
   cout << "    Bob Win %: " << float(bobWins) / NUMDUELS * 100 << endl;
   cout << "Charlie Win %: " << float(charlieWins) / NUMDUELS * 100 << endl;

   return 0;
}

// This function returns if the person getting shot at gets hit or not
void shoot(bool &isAlive, double accuracy)
{
    isAlive = true;

    // This if statement gets a random float between 0 and 1
    if (static_cast<float> (rand()) / static_cast<float> (RAND_MAX) < accuracy)
    {
       isAlive = false;
    }
}

// This function starts the duel and returns the winner
int startDuel()
{
   // Declaring constants and variables
   const float AARONACCURACY = 1.0 / 3.0;
   const float BOBACCURACY = 0.5;
   const float CHARLIEACCURACY = 1.0;
   bool charlieAlive = true;
   bool bobAlive = true;
   bool aaronAlive = true;

   // Starting the duel, making sure the loop will keep running until there's only one winner
   do
   {
      // Aaron shooting, targeting Charlie first, then Bob, but intentionally missing his first shot
      if (bobAlive && charlieAlive && aaronAlive)
      {
         shoot(charlieAlive, 0);
      }
      else if (aaronAlive)
      {
         if (charlieAlive)
         {
            shoot(charlieAlive, AARONACCURACY);
         }
         else
         {
            shoot(bobAlive, AARONACCURACY);
         }
      }

      // Bob shooting, targeting Charlie first, then Aaron
      if (bobAlive)
      {
         if (charlieAlive)
         {
            shoot(charlieAlive, BOBACCURACY);
         }
         else
         {
            shoot(aaronAlive, BOBACCURACY);
         }
      }

      // Charlie shooting, targeting Bob first, then Aaron
      if (charlieAlive)
      {
         if (bobAlive)
         {
            shoot(bobAlive, CHARLIEACCURACY);
         }
         else
         {
            shoot(aaronAlive, CHARLIEACCURACY);
         }
      }

   // Making sure there's only one person alive if the loop is going to end
   }while(!isOneAlive(aaronAlive, bobAlive, charlieAlive));

   // Once it's been confirmed that there's only one person left alive, a winner is returned in the form of an int
   if (aaronAlive)
   {
      // If Aaron is the winner, 0 is returned
      return 0;
   }
   else if (bobAlive)
   {
      // If Bob is alive, 1 is returned
      return 1;
   }
   // If Charlie is alive, 2 is returned
   return 2;
}

// This function returns true if there is only one person left alive
bool isOneAlive(bool aaronAlive, bool bobAlive, bool charlieAlive)
{
   // This if statement will be true if Aaron is the only person alive
   if (aaronAlive && !bobAlive && !charlieAlive)
   {
      return true;
   }

   // This else if statement will be true if Bob is the only person alive
   else if (!aaronAlive && bobAlive && !charlieAlive)
   {
      return true;
   }

   // This else if statement will be true if Charlie is the only person alive
   else if (!aaronAlive && !bobAlive && charlieAlive)
   {
      return true;
   }

   // If more than one person is alive, false will be returned
   return false;
}
