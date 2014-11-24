#include <iostream>

#include "integral.h"
#include <functional>

using namespace std;

double cube(double x) 
{
	return x * x * x;
}

int main()
{
	Integral integral;
	cout << "Integral x^3 = ";
	cout << integral.calculate(cube) << endl;
	cout << "Integral x^3 = ";
	cout << integral.calculate([](double x) { return x*x*x; }) << endl;
	return 0;
}