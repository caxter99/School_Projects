// Devin Hopkins
// 4190350

#include "Point.hpp"

void Point::setPoint(int newX, int newY)
{
	_x = newX;
	_y = newY;
}

void Point::displayPoint()
{
	std::cout << "(" << _x << ", " << _y << ")" << std::endl;
}