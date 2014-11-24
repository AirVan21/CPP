#include "rectangle.h"

Rectangle::Rectangle(Point topLeft, Point bottomRight) : Shape(topLeft, bottomRight)
{}

double Rectangle::area() const
{
	int width = mBottomRight.mX - mTopLeft.mX;
	int height = mTopLeft.mY - mBottomRight.mY;
	return width * height;
}

double Rectangle::perim() const
{
	int width = mBottomRight.mX - mTopLeft.mX;
	int height = mTopLeft.mY - mBottomRight.mY;
	return (width + height) * 2;
}

Rectangle::~Rectangle()
{}