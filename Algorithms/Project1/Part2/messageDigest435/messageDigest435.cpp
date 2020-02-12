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
//./messageDigest435 v file.txt signature_file

// const variables
const std::string EN_FILENAME = "e_n.txt"; // The filename of the file that will store the key(e, n)
const std::string DN_FILENAME = "d_n.txt"; // The filename of the file that will store the key(d, n)
const std::string SIGNATURE_FILENAME = "signature_file"; // The filename of the file that will store the coded message
 
int main(int argc, char *argv[])
{
   if (!(argc == 3 && argv[1][0] == 's') && !(argc == 4 && argv[1][0] == 'v'))
   {
      std::cout << "wrong format! should be \"a.exe s file.txt\"\n";
      std::cout << "                     or \"a.exe v file.txt signature_file\"";
   }
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

         // Making the original message into an integer
         BigInteger originalMessageInt = BigInteger(BigUnsignedInABase(sha256(memblock), 16));

         // Reading in integers d and n from the file
         std::ifstream dnFile;
         dnFile.open(DN_FILENAME);
         std::string dString, nString;
         getline(dnFile, dString);
         getline(dnFile, nString);
         dnFile.close();

         // Creating integers d and n out of the strings of d and n
         BigUnsignedInABase d = BigUnsignedInABase(dString, 10);
         BigUnsignedInABase n = BigUnsignedInABase(nString, 10);

         // Encrypting the original message
         BigUnsigned codedMessage = modexp(originalMessageInt, d, n);

         // Writing the newly encrpyted message to the file
         std::ofstream newFile;
         newFile.open(SIGNATURE_FILENAME);
         newFile << codedMessage;
         newFile.close();

         // Letting the user know the document was signed
         std::cout << "The document was signed.\n";
      }
      else
      {
         // Letting the user know what's going on
         std::cout << "\nVerifying the doc...\n";

         // Making the original message into an integer
         BigUnsigned originalMessageInt = BigUnsigned(BigUnsignedInABase(sha256(memblock), 16));

         // Getting the encrpyted message integer in the form of a string from the original file
         std::string sigFilename = argv[3];
         std::ifstream messageFile;
         messageFile.open(sigFilename);
         std::string codedMessageString;
         getline(messageFile, codedMessageString);
         messageFile.close();

         // Reading in integers e and n from the file
         std::ifstream enFile;
         enFile.open(EN_FILENAME);
         std::string eString, nString;
         getline(enFile, eString);
         getline(enFile, nString);
         enFile.close();

         // Making e and n into integers from strings
         BigUnsigned e = BigUnsignedInABase(eString, 10);
         BigUnsigned n = BigUnsignedInABase(nString, 10);

         // Getting the encrpyted message integer by using the string from earlier
         BigUnsigned codedMessage = BigUnsigned(BigUnsignedInABase(codedMessageString, 10));

         // Decrpyting the coded message
         BigUnsigned oldMessage = modexp(codedMessage, e, n);

         // Checking to see if they're the same or not (they should be). If they're the same,
         // they're authentic. Otherwise, someone's hacked in!
         if (oldMessage == originalMessageInt)
         {
            std::cout << "The document IS authentic.\n";
         }
         else
         {
            std::cout << "The document IS NOT authentic.\n";
         }

         // Letting the user know the document has been checked for authenticity
         std::cout << "The document has been checked for authenticity, with the results diplayed above.\n";
      }
      delete[] memblock;
    }

    // MAking sure the program ends with a newline
    std::cout << "\n";

    return 0;
}