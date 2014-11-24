#pragma once 

#include "StackElement.h"

class Stack{

public:

	Stack();

	void push(int param);

	int pop();

	/*
		Get's or modifies value of element on top of the Stack
	*/
	int& topStack();

	/*
		Product of elements on Stack
	*/
	long product();

private:
	// Pointer to the top
	StackElement *top;
	// Stores product of all elements
	long accum;
	// Amount of zeros in Stack
	int zero;
};
