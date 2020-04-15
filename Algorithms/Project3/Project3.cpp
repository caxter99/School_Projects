
// Devin Hopkins
// 4190350

/// This is my main file for Project 3.

// Include
#include <string>
#include <iostream>
#include "BitMap.hpp"

// Constants
const std::string TWO_BALLS_IMAGE_FILEPATH = "Images/twoBalls.pbm";
const std::string TEST3x8_IMAGE_FILEPATH = "Images/test3x8.pbm";
const std::string TEST28x3_IMAGE_FILEPATH = "Images/test28x3.pbm";
const std::string BUG_IMAGE_FILEPATH = "Images/bug.pbm";
const std::string BUTCHEL_IMAGE_FILEPATH = "Images/Butchel/pbm";
const std::string MONA_LISA_IMAGE_FILEPATH = "Images/Mona Lisa.pbm";
const std::string CAS_IMAGE_FILEPATH = "Images/CAS.pbm";


int main(int argc, char const *argv[])
{
	// Creating a Bit Map for the twoBalls image
	BitMap twoBallsBitMap = BitMap(TEST3x8_IMAGE_FILEPATH);

	// Viewing the bit map
	twoBallsBitMap.viewBitMap();

	// Ending the program fine
	return 0;
}