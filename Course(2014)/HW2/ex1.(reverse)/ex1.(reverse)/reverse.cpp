#include <stdio.h>
#include <iostream>

using namespace std;

/*
	Reverse array function using pointers
*/
void reverseArray(int *arr, int length) {
	int middle = length / 2;
	int *start = arr;
	int *end = arr + length - 1;
	int save = 0;
	while (start - arr < middle) {
		save = *start;
		*start = *end;
		*end = save;
		start++;
		end--;
	}
}

/*
	Ouput
*/
void outputArray(int *arr, int length) {
	cout << "Reversed array:\n";
	for( int *p = arr; p - arr < length; p++) {
		cout << " " << *p;
	}
	cout << "\n";
}

// Array's dimension
const int dimension = 7;

int main() {
	int array1[dimension] = {1, 2, 3, 4, 5, 6, 7};
	reverseArray(array1, dimension);
	outputArray(array1, dimension);
	return 0;
}
