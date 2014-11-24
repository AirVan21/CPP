#include <stdio.h>
#include <iostream>

using namespace std;

const int dimension = 100;

/*
	Compares strings strOne & strTwo
	If '==' => true
	If '!=' => false
*/
bool compareString(const char *strOne, const char *strTwo)
{
	while (*strOne != '\0' && *strTwo != '\0') {
		if (*strOne != *strTwo) {
			return false;
		}
		strOne++;
		strTwo++;
	}
	return *strOne == *strTwo;;
}

int main()
{
	char str1[dimension];
	char str2[dimension];
	cout << "Input str1 = ";
	cin.getline(str1, dimension);
	cout << "Input str2 = ";
	cin.getline(str2, dimension);
	cout << "Answer = " << compareString(str1, str2) << "\n";
	return 0;
}