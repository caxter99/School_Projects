
// Devin Hopkins
// 4190350

/// This is my main file for Project 3.

// Include
#include <string>
#include <iostream>
#include "BitMap.hpp"

// Constants
const std::string TWO_BALLS_IMAGE_FILEPATH = "twoBalls.pbm";
const std::string TEST3x8_IMAGE_FILEPATH = "test3x8.pbm";
const std::string TEST28x3_IMAGE_FILEPATH = "test28x3.pbm";
const std::string BUG_IMAGE_FILEPATH = "bug.pbm";
const std::string BUTCHEL_IMAGE_FILEPATH = "Butchel.pbm";
const std::string MONA_LISA_IMAGE_FILEPATH = "Mona Lisa.pbm";
const std::string CAS_IMAGE_FILEPATH = "CAS.pbm";
const std::string IMAGE_PREFIX = "Images/";


int main(int argc, char const *argv[])
{
	// THIS IS FOR TESTING ONLY
	std::string imageName = IMAGE_PREFIX + TEST3x8_IMAGE_FILEPATH;
	int horizontalSeamsToRemove = 0;
	int verticalSeamsToRemove = 0;

	// Creating a bit map for the twoBalls image
	BitMap bitMap = BitMap(imageName);
	if (!bitMap.hasBitMapLoaded())
	{
		// Attempting to load the file as though it was in the same directory as the the program, since loading
		// the image in the Images directory didn't work
		bitMap.loadBitMap(imageName.substr(IMAGE_PREFIX.length(), imageName.length()));
		if (!bitMap.hasBitMapLoaded())
		{
			std::cout << "The pbm file \"" << imageName << "\" could not be opened.\n";
			std::cout << "This means that the image name was incorrect and/or the file is not formatted properly.\n";
			return 0;
		}
	}

	// Viewing the bit map
	//bitMap.viewBitMap(); // TESTING LINE

	// Ending the program fine
	return 0;
}