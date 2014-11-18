#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

enum stateList {startState, got_, got_S, got_SO, got_SOS};

/*
	Building an automata for string processing
*/
unsigned int processString(string& inputStr)
{
	unsigned int sosSubStrAmount = 0;
	stateList state = startState;
	// Parsing part
	for (char& inputChar : inputStr) {
		switch (inputChar)
		{
			case 'S': 
				// '_S'***
				if (state == got_) {
					state = got_S;
				}
				// '_S0S'***
				else if (state == got_SO) {
					state = got_SOS;
				}
				else {
					state = startState;
				}
				break;

			case 'O': 
				// ' SO'***
				if (state == got_S) {
					state = got_SO;
				}
				else {
					state = startState;
				}
				break;

			case ' ': 
				// ' '***
				if (state == startState) {
					state = got_;
				}
				// ' SOS '***
				else if (state == got_SOS) {
					state = got_;
					sosSubStrAmount++;
				}
				else {
					state = startState;
				}
				break;
			
			default:
				state = startState;
				break;
		}
	}
	
	return sosSubStrAmount;
}

int main()
{
	string inputStr;
	// Input line where is possible to find a SOS substing
	getline(cin, inputStr);
	unsigned int sosCounter = processString(inputStr);
	cout << "Amount of SOS signals = " << sosCounter << endl;
}