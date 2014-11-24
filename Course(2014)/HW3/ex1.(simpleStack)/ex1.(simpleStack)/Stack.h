#pragma once 
#include <iostream>

const int dimension = 100;

class Stack{

public:

	Stack();

	void push(int param);

	int pop();

private:

	// Length of array
	int length;

	// Main array
	int source[dimension];

	// Pointer to the top
	int *top;
};
