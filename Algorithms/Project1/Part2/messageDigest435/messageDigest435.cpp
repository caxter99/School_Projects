/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

// Function headers
void display(char chr[], int sizeOfArray); // Displays the char array

// const variables
const std::string PQ_FILENAME = "p_q.txt"; // The filename of the file that will store the integers p and q
const std::string EN_FILENAME = "e_n.txt"; // The filename of the file that will store the key(e, n)
const std::string DN_FILENAME = "d_n.txt"; // The filename of the file that will store the key(d, n)
const std::string SIGNATURE_FILENAME = "file.txt.signature"; // The filename of the file that will store the coded message
 
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

         std::ifstream dnFile;
         dnFile.open(DN_FILENAME);
         std::string dString, nString;
         getline(dnFile, dString);
         getline(dnFile, nString);
         dString = dString.substr(0, dString.length() - 1);
         nString = nString.substr(0, nString.length() - 1);

         BigUnsignedInABase d = BigUnsignedInABase(dString, 10);
         BigUnsignedInABase n = BigUnsignedInABase(nString, 10);


         dnFile.close();

         //EN_FILENAME
         //BigInteger d = 

         /*// Getting how long the string is
         const int HASH_SIZE = messageString.length();
         const int CHAR_ARRAY_SIZE = HASH_SIZE + 1;

         // Creating and copying the string to a char array
         char messageCharArray[CHAR_ARRAY_SIZE];
         strcpy(messageCharArray, messageString.c_str());

         // Displaying both the string and char array
         std::cout << "string:" << messageString << ":\nchar a:";
         display(messageCharArray, CHAR_ARRAY_SIZE);*/

         BigUnsignedInABase tempMessage = BigUnsignedInABase(messageString, 16);
         BigInteger message = BigInteger(tempMessage);
         BigUnsigned codedMessage = modexp(message, d, n);
         std::cout << "messageString:" << messageString << ":\n";
         std::cout << "  tempMessage:" << tempMessage << ":\n";
         std::cout << "      message:" << message << ":\n";
         std::cout << "            d:" << d << ":\n";
         std::cout << "            n:" << n << ":\n";
         std::cout << " codedMessage:" << codedMessage << ":\n";

         std::ofstream newFile;

         newFile.open(SIGNATURE_FILENAME);
         newFile << codedMessage;

         newFile.close();

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





