
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

	// Setting _hasBitMapLoaded to true since a bit map has been loaded
	_hasBitMapLoaded = true;

	// Closing the file
	input.close();
}

void BitMap::saveBitMap(std::string filepath)
{
	// Making sure something is loaded and it's not empty
	if (!_hasBitMapLoaded)
	{
		std::cout << "Please load a bit map before trying to save it.\n";
		return;
	}
	else if (_isEmpty)
	{
		std::cout << "The current bit map has had so many seams removed, it's currently empty.\n";
		std::cout << "Therefore, nothing will be saved. Please try again with removing less seams.\n";
		return;
	}

	// Gathering everything to write
	std::string stringToWrite = "P2\n";
	stringToWrite += "# Created by a program of Devin Hopkins'\n";
	stringToWrite += std::to_string(_bitMap.at(0).size()) + " " + std::to_string(_bitMap.size()) + "\n";
	stringToWrite += "255\n";
	for (int y = 0; y < _bitMap.size(); y++)
	{
		for (int x = 0; x < _bitMap.at(y).size(); x++)
		{
			if (x != _bitMap.at(y).size() - 1)
			{
				stringToWrite += std::to_string(_bitMap.at(y).at(x)) + " ";
			}
			else
			{
				stringToWrite += std::to_string(_bitMap.at(y).at(x)) + "\n";
			}
		}
	}

	// Opening, writing to, and closing the file
	std::ofstream output;
	output.open(filepath);
	output << stringToWrite;
	output.close();
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
	if (!_hasBitMapLoaded)
	{
		std::cout << "Please load a bit map before trying to display it.\n";
		return;
	}

	// Displaying the basic info
	std::cout << "\nBit Map Info\n";
	std::cout << "Filepath: " << _bitMapFilepath << "\n";
	std::cout << "Type: " << _type << "\n";
	std::cout << "Width x Height: " << _width << " x " << _height << "\n";
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

void BitMap::removeHorizontalSeams(int numberOfSeams)
{
	// Making sure the number is greater than 0 to save some time
	if (numberOfSeams <= 0)
	{
		return;
	}

	// Transpose the image
	transpose();

	// Removing as many seams as sent in
	removeVerticalSeams(numberOfSeams);

	// Undo the transpose
	transpose(true);
}

void BitMap::transpose(bool reverse)
{
	// Creating a copy of the bit map
	std::vector<std::vector<int>> newBitMap;

	// Seeing if the image needs transposed or reversed back to normal
	if (reverse) // Needs reversed back to normal
	{
		// Switch the width and the height
		int temp = _height;
		_height = _width;
		_width = temp;

		// Initializing the new bitmap
		for (int y = 0; y < _height; y++)
		{
			newBitMap.push_back(std::vector<int>());
			for (int x = 0; x < _width; x++)
			{
				newBitMap.at(y).push_back(0);
			}
		}

		// Transposing the old bitmap into the new bitmap
		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				newBitMap.at(y).at(x) = _bitMap.at(x).at(y);
			}
		}
	}
	else // Needs transposed
	{
		// Initializing the new bitmap
		for (int y = 0; y < _width; y++)
		{
			newBitMap.push_back(std::vector<int>());
			for (int x = 0; x < _height; x++)
			{
				newBitMap.at(y).push_back(0);
			}
		}

		// Transposing the old bitmap into the new bitmap
		for (int y = 0; y < _height; y++)
		{
			for (int x = 0; x < _width; x++)
			{
				newBitMap.at(x).at(y) = _bitMap.at(y).at(x);
			}
		}

		// Switch the width and height
		int temp = _height;
		_height = _width;
		_width = temp;
	}

	// Copying the new bitmap into the old bitmap
	copy(&newBitMap, &_bitMap);
}

void BitMap::copy(std::vector<std::vector<int>>* theOriginal, std::vector<std::vector<int>>* theCopy)
{
	// Just in case the copy is already set up
	theCopy->clear();

	// Copying the original to the copy
	for (int y = 0; y < theOriginal->size(); y++)
	{
		theCopy->push_back(std::vector<int>());
		for (int x = 0; x< theOriginal->at(y).size(); x++)
		{
			theCopy->at(y).push_back(theOriginal->at(y).at(x));
		}
	}
}

void BitMap::removeVerticalSeams(int numberOfSeams)
{
	// Making sure the bitmap isn't empty. If it is, return with a message
	if (_isEmpty)
	{
		std::cout << "Warning! You tried to remove too many seams. The image is now gone and another seam\n";
		std::cout << "was attempted to be taken out.\n";
		return;
	}

	// Making sure we won't be removing more seams than possible
	if (numberOfSeams > _width)
	{
		numberOfSeams = _width;
	}

	// Removing as many seams as sent in
	for (int seam = 0; seam < numberOfSeams; seam++)
	{
		removeVerticalSeam();
	}

	// Checking to see if the bitmap is empty or not
	if (_width <= 0 || _height <= 0)
	{
		_isEmpty = true;
	}
}

void BitMap::removeVerticalSeam()
{
	// Creating the energy maps
	std::vector<std::vector<int>> energyMap;
	std::vector<std::vector<int>> cumulativeEnergyMap;

	// Getting them to be the same size as the bit map
	for (int y = 0; y < _height; y++)
	{
		energyMap.push_back(std::vector<int>());
		cumulativeEnergyMap.push_back(std::vector<int>());
		for (int x = 0; x < _width; x++)
		{
			energyMap.at(y).push_back(0);
			cumulativeEnergyMap.at(y).push_back(0);
		}
	}

	// Filling out the energy tables
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			// Grabbing the spot's energy
			int totalEnergyInSpot = 0;
			int currentSpotsEnergy = _bitMap.at(y).at(x);
			if (x > 0)
			{
				totalEnergyInSpot += abs(_bitMap.at(y).at(x - 1) - currentSpotsEnergy);
			}
			if (x < _width - 1)
			{
				totalEnergyInSpot += abs(_bitMap.at(y).at(x + 1) - currentSpotsEnergy);
			}
			if (y > 0)
			{
				totalEnergyInSpot += abs(_bitMap.at(y - 1).at(x) - currentSpotsEnergy);
			}
			if (y < _height - 1)
			{
				totalEnergyInSpot += abs(_bitMap.at(y + 1).at(x) - currentSpotsEnergy);
			}

			// Storing the spot's energy in the table
			energyMap.at(y).at(x) = totalEnergyInSpot;

			// Getting the cumulative energy for the spot
			if (y != 0) // This is for anything but the first row
			{
				int minEnergy = cumulativeEnergyMap.at(y - 1).at(x);
				if (x > 0 && cumulativeEnergyMap.at(y - 1).at(x - 1) < minEnergy)
				{
					minEnergy = cumulativeEnergyMap.at(y - 1).at(x - 1);
				}
				if (x < _width - 1 && cumulativeEnergyMap.at(y - 1).at(x + 1) < minEnergy)
				{
					minEnergy = cumulativeEnergyMap.at(y - 1).at(x + 1);
				}
				cumulativeEnergyMap.at(y).at(x) = totalEnergyInSpot + minEnergy;
			}
			else // This is for the first row
			{
				cumulativeEnergyMap.at(y).at(x) = totalEnergyInSpot;
			}
		}
	}

	// Finding the spot on the bottom row with the lowest energy and removing it
	int minEnergyPos = 0;
	int minEnergy = cumulativeEnergyMap.at(_height - 1).at(minEnergyPos);
	for (int x = 1; x < _width; x++)
	{
		if (cumulativeEnergyMap.at(_height - 1).at(x) < minEnergy)
		{
			minEnergy = cumulativeEnergyMap.at(_height - 1).at(x);
			minEnergyPos = x;
		}
	}
	_bitMap.at(_height - 1).erase(_bitMap.at(_height - 1).begin() + minEnergyPos);

	// Removing the seam with the lowest energy
	for (int y = _height - 2; y >= 0; y--)
	{
		int tempMinEnergyLocation = minEnergyPos;
		if (minEnergyPos > 0)
		{
			minEnergy = cumulativeEnergyMap.at(y).at(minEnergyPos - 1);
			tempMinEnergyLocation -= 1;

			if (cumulativeEnergyMap.at(y).at(minEnergyPos) < minEnergy)
			{
				minEnergy = cumulativeEnergyMap.at(y).at(minEnergyPos);
				tempMinEnergyLocation = minEnergyPos;
			}
		}
		else
		{
			minEnergy = cumulativeEnergyMap.at(y).at(minEnergyPos);
		}
		if (minEnergyPos < _width - 1 && cumulativeEnergyMap.at(y).at(minEnergyPos + 1) < minEnergy)
		{
			minEnergy = cumulativeEnergyMap.at(y).at(minEnergyPos + 1);
			tempMinEnergyLocation = minEnergyPos + 1;
		}
		minEnergyPos = tempMinEnergyLocation;
		_bitMap.at(y).erase(_bitMap.at(y).begin() + minEnergyPos);
	}

	// Since one bit from each row has been removed, decrement the width
	_width -= 1;
}
