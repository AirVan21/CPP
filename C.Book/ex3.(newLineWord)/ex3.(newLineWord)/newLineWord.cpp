#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

#define OK 0

// Splits string on words
// Prints every word in a new line
void printWordsFromNewLine(string& inputString)
{
	bool newLineFlag = false;

	for (char& symbol : inputString) {
		// New line case
		if (symbol == '\t' || symbol == '\n' || symbol == ' ') {
			if (!newLineFlag)
				cout << endl;
			newLineFlag = true;
		}
		else {
			cout << symbol;
			newLineFlag = false;
		}
	}
}

int main()
{
	cout << "Please, input your string :" << endl;
	string inputString;
	getline(cin, inputString);
	printWordsFromNewLine(inputString);
	return OK;
}