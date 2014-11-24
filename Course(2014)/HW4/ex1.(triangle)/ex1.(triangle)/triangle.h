#pragma once

#include <iostream>
#include "point.h"
// Represents isosceles triangle
class Triangle{

public:
	// Constructor
	Triangle(Point baseOne, Point baseTwo, Point top);
	// Prints side coordinates
	void draw();

protected:
	// Coordinates
	Point mBaseOne;
	Point mBaseTwo;
	Point mTop;
};

