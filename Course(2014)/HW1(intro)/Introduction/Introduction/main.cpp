#include <stdio.h>
#include <iostream>

using namespace std;

const int arrLength = 10;

/*
	ex1
	Calculate series:
	'1/(1)^2 - 1/(3)^2 + 1/(5)^2 - ...
*/
double ex1CalcSeries(int n) {
	double sum = 0;
	double add = 0;
	bool sign = true;
	for (int i = 1; i <= n; i = i + 2) { 
		add = 1.0 / (i * i);
		sum = sign ? sum + add : sum - add; 
		sign = !sign;
	}
	return sum;
}

/*
	ex2
	Calculate intput integers' product
*/
int ex2CalcProduct() {
	int product = 1;
	int input;
	cout << "\nInput you integers:\n";
	cin >> input;
	// for case where first intput = 0
	if (input) {
		while (input) {
			product *= input;
			cin >> input;
		}
	} else {
		product = 0;
	}
	return product;
}

/*
	ex3
	Find last non-zero digit in n!
*/
int ex3FindDigit(int n) {
	unsigned long long factorial = 1;
	// create factorial
	for (int i = 2; i <= n; i++) {
		factorial *= i;
	}
	// cut number
	while(factorial % 10 == 0) {
		factorial = factorial / 10;
	}
	return (factorial % 10);
}

/*
	ex4
	Find length of non-zero part in array
*/
int ex4FindLength(int numArr[]) {
	int length = 0;
	for(int i = 0; i < arrLength; i++) {
		if (*(numArr + i) == 0) {
			length = i;
			break;
		}
	}
	return length;
}

int main() {
	// start value for menu
	char index = 'a';
	int param = 0;
	// Array for ex4
	int numArr[arrLength] = {2, 3, 7, 9, 6, 7, 1, 0, 0, 0};
	cout << "First HW\n";
	while (index != 'q') {
		cout << " Press key to continue:\n";
		cout << " 1 - to test ex1\n";
		cout << " 2 - to test ex2\n";
		cout << " 3 - to test ex3\n";
		cout << " 4 - to test ex4\n";
		cout << " q - for exit\n\n";
		cout << " Input = "; 
		cin >> index;
		switch(index) {
		case '1':
			cout << "\n Press\n n = ";
			scanf("%d", &param);
			cout << "\n Answer = " << ex1CalcSeries(param) << "\n\n";
			break;
		case '2':
			// using param like a help variable
			param = ex2CalcProduct();
			cout << "\n Answer = " << param << "\n\n";
			break;
		case '3':
			cout << "\n Press\n n = ";
			scanf("%d", &param);
			cout << "\n Answer = " << ex3FindDigit(param) << "\n\n";
			break;
		case '4':
			cout << "\n For current array answer = " << ex4FindLength(numArr) << "\n\n";
			break;
		case 'q':
			cout << "\nGoodbye!\n";
			break;
		default :
			cout << "\n Wrong choice! Try again\n\n";
			break;
		}
	}
	return 0;
}