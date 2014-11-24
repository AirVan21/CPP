#include <iostream>
#include <stdio.h>

#include "complex.h"

using namespace std;

int main() {
	Complex num1(4, 5);
	Complex num2(2, 10);
	Complex num3 = num1 * num2;
	num1 *= num2;
	return 0;
}