#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int dimension = 3;

/*	
	Set increase order
	@param1 - int number 
	@param2 - int number
	@param3 - int number
*/
void order(int &param1, int &param2, int &param3)
{
	int numArr[dimension] = {param1, param2, param3};
	sort(numArr, numArr + dimension);
	param1 = numArr[0];
	param2 = numArr[1];
	param3 = numArr[2];
}

int main()
{
	int number1 = 7;
	int number2 = 1;
	int number3 = 3;
	cout << "Input:\n";
	cout << number1 << " " << number2 << " " << number3;
	order(number1, number2, number3);
	cout << "\nOutput:\n";
	cout << number1 << " " << number2 << " "<< number3 << "\n";
	return 0;
}