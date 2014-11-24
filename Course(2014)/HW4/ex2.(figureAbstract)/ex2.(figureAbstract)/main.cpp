#include <iostream>

#include "rectangle.h"
#include "circle.h"

using namespace std;

int main()
{	
	Point topLeft(1, 5);
	Point bottomRight(8, 2);
	Rectangle *rect = new Rectangle(topLeft, bottomRight);
	cout << "Rectangle : " << endl;
	cout << "Area = " << rect->area() << " Perim = " << rect->perim() << endl;
	delete rect;
	Circle *circ = new Circle(topLeft, bottomRight);
	cout << "Curcle : " << endl;
	cout << "Area = " << circ->area() << " Perim = " << circ->perim() << endl;
	delete circ;
	return 0;
}