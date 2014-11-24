#include "shape.h"

Shape::Shape(Point nodeOne, Point nodeTwo) :
	mTopLeft(nodeOne),
	mBottomRight(nodeTwo)
{}

Shape::~Shape()
{}