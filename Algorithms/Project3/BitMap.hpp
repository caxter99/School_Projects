
// Devin Hopkins
// 4190350

// Include
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// This class is used for storing bit maps
class BitMap
{
public:
	BitMap();
	BitMap(std::string bitMapFilepath);
	void loadBitMap(std::string bitMapFilepath);
	void saveBitMap(std::string filepath);
	void viewBitMap();
	bool hasBitMapLoaded() { return _hasBitMapLoaded; };
	bool isBitMapEmpty() { return _isEmpty; };
	void removeVerticalSeams(int numberOfSeams = 1);
	void removeHorizontalSeams(int numberOfSeams = 1);

private:
	// Functions
	void createBitMap(std::ifstream* input);
	void removeVerticalSeam();
	void transpose(bool reverse = false);
	void copy(std::vector<std::vector<int>>* theOriginal, std::vector<std::vector<int>>* theCopy);

	// Variables
	std::string _bitMapFilepath = ""; // The map's filepath
	std::string _type = ""; // The type of bit map (right now only P2 is allowed)
	int _height = -1; // The height of the map in pixels
	int _width = -1; // The width of the map in pixels
	int _range = -1; // The range of color or greyscale the pixels have
	std::vector<std::vector<int>> _bitMap; // The actual bit map
	bool _hasBitMapLoaded = false; // True if this object has a bit map loaded, false otherwise
	bool _isEmpty = false; // True if all of the seams have been removed
};