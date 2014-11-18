#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

#define OK 0;

// Function for double space correction
void formattedOutput(string& inputStr)
{
	// marker for double space s
	bool alreadySpace = false;

	for (char& symbol : inputStr) {
		if (symbol == ' ') {
			// first space case
			if (!alreadySpace) {
				// turn on flag
				alreadySpace = true;
				cout << symbol;
			}
		}
		else {
			cout << symbol;
			alreadySpace = false;
		}
	}
}

int main()
{
	string inputString;
	cout << "Please, input string :\n";
	getline(cin, inputString);
	formattedOutput(inputString);
	cout << endl;
	return OK;
}