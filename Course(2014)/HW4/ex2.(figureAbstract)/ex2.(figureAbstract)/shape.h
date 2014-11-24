#pragma once
#include "point.h"

// Represents abstract figure
class Shape
{
public:

	Shape(Point nodeOne, Point nodeTwo);
	~Shape();
	// Perimeter
	virtual double perim() const = 0;
	// Square
	virtual double area() const = 0;

protected:

	Point mTopLeft;
	Point mBottomRight;
};
