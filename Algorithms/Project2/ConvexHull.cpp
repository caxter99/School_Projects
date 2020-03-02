// Devin Hopkins
// 4190350

#include "ConvexHull.hpp"

void ConvexHull::readFile(std::string filename)
{
	// Creating a file reading object
	std::ifstream inputFile;
	inputFile.open(filename);
	if (inputFile)
	{
		// Creating the variables that are needed
		std::string tempString = "";
		int num1, num2;

		// Lopping through the entire file to get all of the data
		while(!inputFile.eof())
		{
			// Getting the points from the line
			getline(inputFile, tempString);
			num1 = stoi(tempString.substr(0, tempString.find("\t")));
			num2 = stoi(tempString.substr(tempString.find("\t") + 1));

			// Creatting a point from the data gathered
			Point p;
			p.setPoint(num1, num2);
			_pointVector.push_back(p);
		}
	}
	else
	{
		std::cout << "failure" << std::endl;
	}
	inputFile.close();
}

void ConvexHull::printPointVector()
{
	for (std::vector<Point>::iterator iter = _pointVector.begin(); iter != _pointVector.end(); iter++)
	{
		iter->displayPoint();
	}
}