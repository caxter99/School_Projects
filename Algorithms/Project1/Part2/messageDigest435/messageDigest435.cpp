/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

// PUT THIS INTO COMMAND LINE TO DO PART 1
//./messageDigest435 s file.txt
// THEN, PUT THIS INTO COMMAND LINE TO DO PART 2
//./messageDigest435 v file.txt.signature

// Function headers
void display(char chr[], int sizeOfArray); // Displays the char array

// const variables
const std::string EN_FILENAME = "e_n.txt"; // The filename of the file that will store the key(e, n)
const std::string DN_FILENAME = "d_n.txt"; // The filename of the file that will store the key(d, n)
const std::string SIGNATURE_FILENAME = "file.txt.signature.Copy"; // The filename of the file that will store the coded message
 
int main(int argc, char *argv[])
{
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
         std::string originalMessageString = sha256(memblock);
         std::cout << "message string:" << originalMessageString << std::endl;

         std::ifstream enFile;
         enFile.open(EN_FILENAME);
         std::string eString, nString;
         getline(enFile, eString);
         getline(enFile, nString);
         enFile.close();

         BigUnsignedInABase e = BigUnsignedInABase(eString, 10);
         BigUnsignedInABase n = BigUnsignedInABase(nString, 10);

         //BigUnsignedInABase tempMessage = BigUnsignedInABase(messageString, 16);
         //BigInteger message = BigInteger(tempMessage);
         BigInteger originalMessage = BigInteger(BigUnsignedInABase(originalMessageString, 16));
         //                         modexp(base, exponent, mod)
         BigUnsigned codedMessage = modexp(originalMessage, e, n);
         /*std::cout << "messageString:" << messageString << ":\n";
         std::cout << "  tempMessage:" << tempMessage << ":\n";
         std::cout << "      message:" << message << ":\n";
         std::cout << "            e:" << e << ":\n";
         std::cout << "            n:" << n << ":\n";*/
         //std::cout << " originalMessage:" << originalMessage << ":\n";
         //std::cout << "    codedMessage:" << codedMessage << ":\n";

         std::ofstream newFile;

         newFile.open(SIGNATURE_FILENAME);
         newFile << codedMessage;

         newFile.close();

      }
      else
      {
         std::cout << "\nVerifying the doc...\n";

         std::string originalMessageString = sha256(memblock);
         std::cout << "message string:" << originalMessageString << std::endl;
         
         // Getting the original message into an integer
         /*std::string originalMessageString = sha256(memblock);
         BigUnsignedInABase originalMessageInt = BigUnsignedInABase(originalMessageString, 16);
         BigUnsigned OGMessage = BigUnsigned(originalMessageInt);*/
         BigUnsigned originalMessageInt = BigUnsigned(BigUnsignedInABase(sha256(memblock), 16));

         std::ifstream messageFile;
         messageFile.open(SIGNATURE_FILENAME);
         std::string codedMessageString;
         getline(messageFile, codedMessageString);
         messageFile.close();

         std::ifstream dnFile;
         dnFile.open(DN_FILENAME);
         std::string dString, nString;
         getline(dnFile, dString);
         getline(dnFile, nString);
         dnFile.close();

         BigUnsignedInABase tempCodedMessage = BigUnsignedInABase(codedMessageString, 10);
         BigUnsigned codedMessage = BigUnsigned(tempCodedMessage);
         BigUnsigned d = BigUnsignedInABase(dString, 10);
         BigUnsigned n = BigUnsignedInABase(nString, 10);

         //                       modexp(base, exponent, mod)
         BigUnsigned oldMessage = modexp(codedMessage, d, n);

         /*std::cout << "        oldMessage:" << oldMessage << ":\n";
         std::cout << "originalMessageInt:" << originalMessageInt << ":\n";
         std::cout << "      codedMessage:" << codedMessage << ":\n";*/

         if (oldMessage == originalMessageInt)
         {
            std::cout << "they're the same!\n";
         }
         else
         {
            std::cout << "they're not the same\n";
         }
      }
      delete[] memblock;
    }

    // MAking sure the program ends with a newline
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





