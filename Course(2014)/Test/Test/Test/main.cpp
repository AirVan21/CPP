#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	std::cout << sizeof(int);
	int array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int *pointer = array; pointer != array + 10; pointer++) {
		cout << *pointer;
	}
}