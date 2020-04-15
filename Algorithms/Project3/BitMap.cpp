
// Devin Hopkins
// 4190350

// This file is used for storing bit maps

// Include
#include "BitMap.hpp"

BitMap::BitMap()
{
	// Do nothing
}

BitMap::BitMap(std::string bitMapFilepath)
{
	// Load the map in
	loadBitMap(bitMapFilepath);
}

void BitMap::loadBitMap(std::string bitMapFilepath)
{
	// Attempting to open the map's filepath
	std::ifstream input(bitMapFilepath);

	// Making sure the file opened correctly
	if (input.fail())
	{
		return;
	}

	// Reading in the first number and making sure it's correct
	std::string type = "";
	input >> type;
	if (type != "P2")
	{
		input.close();
		return;
	}

	// Saving the filename and type so the bit map can remember it
	_bitMapFilepath = bitMapFilepath;
	_type = type;

	// Grabbing the width, height, and range of the map
	std::string strWidth, strHeight, strRange, throwAway;
	getline(input, throwAway); // This gets the "\n" form the first line
	getline(input, throwAway); // This gets the comment in the second line (including the "\n")
	input >> strWidth >> strHeight;
	getline(input, throwAway); // This gets the "\n" from the third line
	input >> strRange;
	getline(input, throwAway); // This gets the "\n" from the fourth line	
	_width = stoi(strWidth);
	_height = stoi(strHeight);
	_range = stoi(strRange);

	// Creating the bit map
	createBitMap(&input);

	// Closing the file
	input.close();
}

void BitMap::createBitMap(std::ifstream* input)
{
	// Variables
	std::string strPixValue = ""; // Temporarily holds a pixel's value as it is grabbed from the bit map

	// Looping through, grabbing each pixel's value
	for (int y = 0; y < _height; y++)
	{
		std::vector<int> tempIntVector;
		_bitMap.push_back(tempIntVector);
		for (int x = 0; x < _width; x++)
		{
			// Grabbing the pixel's value and storing it
			(*input) >> strPixValue;
			_bitMap.at(y).push_back(stoi(strPixValue));
		}
	}
}

void BitMap::viewBitMap()
{
	// Making sure this funciton isn't called early, before a bit map has been set up
	if (_width <= 0 || _height <= 0)
	{
		std::cout << "Please load a bit map before trying to display it\n";
		return;
	}

	// Displaying the basic info
	std::cout << "\nBit Map Info\n";
	std::cout << "Filepath: " << _bitMapFilepath << "\n";
	std::cout << "Type: " << _type << "\n";
	std::cout << "Width x Height:" << _width << " x " << _height << "\n";
	std::cout << "Range: " << _range << "\n";
	std::cout << "Map:\n";

	// Looping through the vector and displaying everything
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			std::cout << _bitMap.at(y).at(x) << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}




