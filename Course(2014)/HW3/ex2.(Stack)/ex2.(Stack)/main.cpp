#include <iostream>
#include <stdio.h>
#include "Stack.h"

using namespace std;

int main()
{
	Stack stack;
	stack.push(3);
	stack.push(5);
	cout << "Test stack:\n";
	cout << stack.product() << "\n";
	cout << stack.pop() << "\n";
	cout << stack.product() << "\n";
	stack.push(0);
	cout << stack.product() << "\n";
}