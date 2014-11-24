#include <stdio.h>
#include <iostream>

using namespace std;

/*
	Doubles int value
	@param - input value
*/
void twice(int *param) 
{
	*param *= *param;
}

int main() {
	int number = 7;
	cout << "Source value = " << number << "\n";
	twice(&number);
	cout << "Doubled value = " << number << "\n";
	return 0;
}