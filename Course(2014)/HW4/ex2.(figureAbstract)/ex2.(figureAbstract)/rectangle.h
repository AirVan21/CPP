#include "shape.h"

class Rectangle : public Shape
{
public:

	Rectangle(Point topLeft, Point bottomRight);
	~Rectangle();
	
	double perim() const;
	double area() const;

};
