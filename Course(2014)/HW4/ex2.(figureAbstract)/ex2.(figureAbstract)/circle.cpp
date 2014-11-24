#include "circle.h"

Circle::Circle(Point topLeft, Point bottomRight) : Shape(topLeft, bottomRight)
{
	mRadius = (bottomRight.mX - topLeft.mX) / 2;
}

double Circle::area() const
{
	return pi * mRadius * mRadius;
}

double Circle::perim() const
{
	return 2 * pi * mRadius;
}

Circle::~Circle()
{}
