#include <stdio.h>
#include <iostream>

#include "rational.h"

using namespace std;

int main()
{
	Rational ratio(1, 3);
	double answer = ratio;
	cout << "Ratio => double = " << answer << endl;
	return 0;
}