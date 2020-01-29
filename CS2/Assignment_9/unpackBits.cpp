/*
   COPYRIGHT (C) 2018 Devin Hopkins (4190350) All rights reserved.
   CSII Assignment 9
   Author.  Devin Hopkins
            djh155@zips.uakron.edu
   Version. 1.01 4.23.2018
   Purpose: This program is the test cases for the assignment
*/
#include <iostream>
#include <iomanip>

// prototypes
void unpackCharacters(char[], unsigned);
void displayBits(unsigned);

int main() {
   char characters[4];
   unsigned packed{1633903975}; // a, c, e, g

   std::cout << "The packed character representation is:\n";
   displayBits(packed);

   // demonstrate unpacking of characters
   unpackCharacters(characters, packed);
   std::cout << "\nThe unpacked characters are: ";
   for (size_t i{0}; i < 4; ++i) {
      std::cout << characters[i] << " ";
   }
   std::cout << std::endl;

   std::cout << "\nThe unpacked characters in bits are:" << std::endl;
   for (size_t i{0}; i < 4; ++i) {
      displayBits(characters[i]);
   }
}

// take apart the characters
void unpackCharacters(char characters[], unsigned pack)
{
    // Declaring the masks necessary for filtering out the bits
    unsigned mask1 = 4278190080;
    unsigned mask2 = 16711680;
    unsigned mask3 = 65280;
    //unsigned mask4 = 255;

    // Getting the character from the packed value
    characters[0] = pack | mask1;

    // Moving the pack over 8 bits to get rid of the first character
    pack >>= 8;

    // Repeat the cycle
    characters[1] = pack | mask2;
    pack >>= 8;
    characters[2] = pack | mask3;
    pack >>= 8;
    characters[3] = pack;
}

// display the bits of value
void displayBits(unsigned value)
{
    // Creating a flag that holds the max of a single, eight bit unsigned value
    unsigned flagMax = 0x80;

    // If the value is less than the flag, then it goes into here to print it out
    if (value <= flagMax)
    {
        // Making a loop to go through the eight digits
        for (unsigned x = 0; x < 8; ++x)
        {
            // Prints out a 1 or 0 depending if the digit matches with 1 from the flagMax
            if (flagMax == (value & flagMax))
            {
                std::cout << "1";
            }
            else
            {
                std::cout << "0";
            }

            // Shifting the value over by one
            value <<= 1;
        }
    }

    // If the value is more than the flag, than it goes into here to be dissected into smaller pieces
    else
    {
        // Since we're dealing with four characters, divides it into four different pieces
        for (int x = 0; x < 4; ++x)
        {
            // Uses recursion to display each piece
            displayBits((value >> (8 * x)) & 0xFF);
        }
    }

    // Makes the output look nice
    std::cout << std::endl;
}







