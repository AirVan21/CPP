#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#define OK 0;

// Counting amount of special sumbols in a string
void stringParse(string& input, int& numOfLines, int& numOfTabs, int& numOfSpaces, int& numOfOther)
{
	for (char& inputChar : input) {
		switch (inputChar)
		{
			// Counts line feeds
		case '\n':  numOfLines++;
			break;
			// Counts tabs
		case '\t': numOfTabs++;
			break;
			// Countrs spaces
		case ' ': numOfSpaces++;
			break;
			// Counts other symbols
		default: numOfOther++;
			break;
		}
	}
}

int main()
{
	int numOfNewLineSymbol = 0;
	int numOfTabSymbol = 0;
	int numOfSpaceSymbol = 0;
	int numOfOutOfScopeSymbol = 0;
	string inputString;
	cout << "Please input a sting :" << endl;
	getline(cin, inputString);
	cout << endl;
	
	stringParse(inputString, numOfNewLineSymbol, numOfTabSymbol, numOfSpaceSymbol, numOfOutOfScopeSymbol);
	int amountOfSymbols = inputString.length();
	int handledSymbols = numOfNewLineSymbol + numOfTabSymbol + numOfSpaceSymbol + numOfOutOfScopeSymbol;
	
	if (amountOfSymbols == handledSymbols) {
		printf("Total amount of symbols: %d\n", amountOfSymbols);
		printf("New Lines     = %d\n", numOfNewLineSymbol);
		printf("New Tabs      = %d\n", numOfTabSymbol);
		printf("New Spaces    = %d\n", numOfSpaceSymbol);
		printf("Other Symblos = %d\n", numOfOutOfScopeSymbol);
	}
	else {
		printf("Parsing goes wrong!");
	}
	
	return OK;
}