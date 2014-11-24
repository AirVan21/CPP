#include <stdio.h>
#include <iostream>

/*
	ex 3a
	Find last digit in product 1 * 3 * 5 .... (2*n + 1) 
*/
int ex3aLastProductDigit(int number) {
	int lastDigit = 1;
	int edge = number * 2 + 1;
	// Calculating last digit
	for (int i = 1; i <= edge; i += 2) {
		lastDigit *= i;
		lastDigit %= 10;
	}
	return lastDigit;
}

/*
	ex3
	Find amount of non-zero digits in the end
*/
int ex3bFindZeros(int n) {
	int fiveCounter = 0;
	for (int i = 2; i <= n; i++) {
		fiveCounter = i % 5 == 0 ? ++fiveCounter : fiveCounter;
	}	
	return fiveCounter;
}

// param for ex 3a
const int param1 = 31;
// param for ex 3b
const int param2 = 20;

int main() {
	int answer1 = ex3aLastProductDigit(param1);
	std::cout << " Exercise 3a\n" << " n = " << param1 << " answer = " << answer1 << "\n"; 
	int answer2 = ex3bFindZeros(param2);
	std::cout << "\n Exercise 3b\n" << " n = " << param2 << " answer = " << answer2 << "\n"; 
	return 0;
}