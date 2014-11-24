#include <stdio.h>
#include <iostream>

using namespace std;

// Dimension of array
int const dimension = 10;

/*
	Initalizes array of integers
	@arr int[]
	@length length of array
*/
void fulfillArray(int *arr, int length)
{
	// Set's to the first element
	int *pointer = arr;
	// Initialize with zero, exept last
	for (; pointer - arr < length - 1; pointer++) {
		*pointer = 0;
	}
	// Initialize last 
	*pointer = 1;
}

/*
	Array output
*/
void outputArray(int *arr, int length)
{
	for(int *pointer = arr; pointer - arr < length; pointer++) {
		cout << *pointer << " ";
	}
	cout << "\n";
}

int main() 
{
	int *arr[dimension];
	// Massive creation
	cout << "Every array printed as a row\n\n";
	for (int i = 0; i < dimension; i++) {
		// Allocates memory array
		arr[i] = new int[i + 1];
		// Init array
		fulfillArray(arr[i], i + 1);
		// Output array
		outputArray(arr[i], i + 1);
	}
	return 0;
}