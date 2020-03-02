// Devin Hopkins
// 4190350

#include "Point.hpp"

void Point::setPoint(int newX, int newY)
{
	x = newX;
	y = newY;
}

void Point::displayPoint()
{
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}