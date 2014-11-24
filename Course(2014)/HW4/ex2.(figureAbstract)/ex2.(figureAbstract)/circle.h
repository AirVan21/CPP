#include "shape.h"

const double pi = 3.141592653;

class Circle : public Shape
{
public:

	Circle(Point topLeft, Point bottomRight);
	~Circle();

	double perim() const;
	double area() const;

private:

	double mRadius;

};