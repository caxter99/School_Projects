/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

// Function headers
void display(char chr[], int sizeOfArray); // Displays the char array
 
int main(int argc, char *argv[])
{
   //demonstrating how sha256 works
   std::string input = "testing";
   std::string output1 = sha256(input);
   std::cout << "sha256('"<< input << "'):" << output1 << "\n";
   
   //demo bigInt works here
   BigUnsigned a = stringToBigUnsigned("124338907642982722929222542626327282");
   BigUnsigned b = stringToBigUnsigned("124338907642977775546469426263278643");
   std::cout << "big a = " <<a<<"\n";
   std::cout << "big b = " <<b<<"\n";
   std::cout << "big a*b = " <<a*b<<"\n";

   //Second part of your project starts here
   if (argc != 3 || (argv[1][0]!='s' && argv[1][0]!='v')) 
      std::cout << "wrong format! should be \"a.exe s filename\"";
   else {
      std::string filename = argv[2];
      
            
      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file
      
      myfile.seekg (0, std::ios::beg);
      char* memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();
      
      std::string copyOFfile = filename+".Copy"; 
      std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
      myfile2.write (memblock, size); //write to a file
      myfile2.close();
      
      //std::cout<<memblock;
        
      if (argv[1][0]=='s') {
         std::cout << "\nSigning the doc...\n";
         
         // Getting the hash string
         std::string messageString = sha256(memblock);

         // Getting how long the string is
         const int HASH_SIZE = messageString.length();
         const int CHAR_ARRAY_SIZE = HASH_SIZE + 1;

         // Creating and copying the string to a char array
         char messageCharArray[CHAR_ARRAY_SIZE];
         strcpy(messageCharArray, messageString.c_str());

         // Displaying both the string and char array
         std::cout << "string:" << messageString << ":\nchar a:";
         display(messageCharArray, CHAR_ARRAY_SIZE);

         //int base10Hash = toNewBase(messageCharArray, CHAR_ARRAY_SIZE);
      }
      else
      {
         std::cout << "\n"<<"Need to verify the doc.\n";
         //.....
      }
      delete[] memblock;
    }

    // It doesn't always end with a newline, so I'm making sure it does
    std::cout << "\n";

    return 0;
}

// Displays the char star
void display(char chr[], int sizeOfArray)
{
   // Looping through and displaying each bit
   for (int i = 0; i < sizeOfArray; i++)
   {
      std::cout << chr[i];
   }

   // Ending on a new line
   std::cout << "\n";
}





