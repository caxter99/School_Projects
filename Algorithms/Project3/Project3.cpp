
// Devin Hopkins
// 4190350

/// This is my main file for Project 3.

// Include
#include <string>
#include <iostream>
#include "BitMap.hpp"

// Constants
const std::vector<std::string> POSSIBLE_IMAGE_NAMES = {"2Balls.pbm", "test3x8.pbm", "test28x3.pbm",
														"bug.pbm", "Butchel.pbm", "MonaLisa.pbm",
														"CAS.pbm"};
const std::string IMAGE_PREFIX = "Images/";
const std::string PROCESSED_IMAGE_PREFIX = "Processed_Images/";


int main(int argc, char const *argv[])
{
	// Variables that the user will enter
	std::string imageName;
	int verticalSeamRemovals, horizontalSeamRemovals;

	// Making sure the correct arguments were given
	bool wrongData = false;
	if (argc != 4) // They entered the wrong number of arguments
	{
		wrongData = true;
	}
	else // They entered the correct number of arguments
	{
		try{
			// Getting the data from the user's command
			imageName = argv[1];
			verticalSeamRemovals = std::stoi(argv[2]);
			horizontalSeamRemovals = std::stoi(argv[3]);

		}catch(std::exception e){ // If they entered something wrong, it will cause an error
			wrongData = true;
		}
	}

	// If the user entered incorrect data, let them know and terminate the program
	if (wrongData)
	{
		std::cout << "\nYou did not enter the information properly. Enter the information like the following:\n";
		std::cout << "./prj <image name> <number of vertical seam removals> <number of horizontal seam removals>\n";
		std::cout << "\n";
		return 0;
	}

	// Creating a bit map for the user entered image
	BitMap bitMap = BitMap(imageName);
	if (!bitMap.hasBitMapLoaded())
	{
		// Attempting to load the file as though it was in the same directory as the the program, since loading
		// the image in the Images directory didn't work
		bitMap.loadBitMap(IMAGE_PREFIX + imageName);
		if (!bitMap.hasBitMapLoaded())
		{
			std::cout << "\nThe pbm file \"" << imageName << "\" could not be opened.\n";
			std::cout << "This means that the image name was incorrect and/or the file is not formatted properly.\n";
			std::cout << "\nHere are the available images:\n";
			for (int x = 0; x < POSSIBLE_IMAGE_NAMES.size(); x++)
			{
				std::cout << POSSIBLE_IMAGE_NAMES.at(x) << "\n";
			}
			std::cout << "\n";
			return 0;
		}
	}

	// Removing all of the vertical and horizontal seams from the image
	bitMap.removeVerticalSeams(verticalSeamRemovals);
	bitMap.removeHorizontalSeams(horizontalSeamRemovals);

	// Writing the image back, so long as it's not empty
	if (bitMap.isBitMapEmpty())
	{
		std::cout << "You removed every seam, so there is no image to save.\n";
	}
	else
	{
		std::string savedFilepath = PROCESSED_IMAGE_PREFIX + imageName.substr(0, imageName.find(".")) + "_processed_";
		savedFilepath += std::to_string(verticalSeamRemovals) + "_" + std::to_string(horizontalSeamRemovals) + ".pbm";
		bitMap.saveBitMap(savedFilepath);
	}

	// Ending the program fine
	return 0;
}