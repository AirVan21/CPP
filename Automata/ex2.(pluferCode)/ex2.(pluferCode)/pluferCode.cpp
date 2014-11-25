#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define OK 0;

/*
	Helpful constants
*/
int const firstNumAscii = '0';
int const nodeAmount = 10;

/*
	Parse input concatenated digits on correct Node-Namings
	(561012) => (5_6_10_12)
*/
void parseInput(string& inputStr, vector<int>& nodeAccum)
{
	int lastAdded = 0;
	int currentNumber = 0;
	for (int i = 0; i < inputStr.length(); i++) {
		// Write extra digit to current number		
		currentNumber += inputStr[i] - firstNumAscii;
		// Define Number borders
		if (currentNumber >= lastAdded) {
			nodeAccum.push_back(currentNumber);
			lastAdded = currentNumber;
			currentNumber = 0;
		} else {
			currentNumber *= 10;
		}
	}
}

/*
	Constract adjacency lists	
*/
void fillGraph(vector<vector<int>>& graph, vector<int>& accumulator)
{
	int lastAdded = 1;
	int linkPoint = *begin(accumulator);
	for (auto i = begin(accumulator); i != end(accumulator); i++) {
		lastAdded = *i == lastAdded ? lastAdded + 1 : lastAdded;
		graph[*i].push_back(lastAdded);
		graph[lastAdded].push_back(*i);
		linkPoint = *i;
		lastAdded++;
	}
}

/*
	Printing Graph
*/
void printGraph(vector<vector<int>>& graph) {
	vector<int> help;
	for (auto i = begin(graph) + 1; i != end(graph); i++) {
		for (auto j = begin(*i); j != end(*i); j++) {
			cout << *j << " ";
		}
		cout << endl;
	}
}

int main()
{
	// Input Accumulator 
	string inputStr;
	// Answer graph
	vector<vector<int>> graph(nodeAmount + 1, vector<int>());
	// Parsed Input Accumulator
 	vector<int> parsedInput;
	cout << "Input Plufer Code = ";
	getline(cin, inputStr);
	// Parse string with Node-Names
	parseInput(inputStr, parsedInput);
	// Filling answer
	fillGraph(graph, parsedInput);
	// Debug
	printGraph(graph);
	return OK;
}