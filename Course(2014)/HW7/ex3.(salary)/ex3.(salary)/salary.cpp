#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<string, int> info;

// Reads input data in pair elements
void readData(vector<info> &tableData)
{
	cout << "Please, input data (name salary) : " << endl;
	cout << "(example: 'Ivanov 50000')\n" << endl;
	info element;
	cin >> element.first;
	while (element.first != "*") {
		cin >> element.second;
		tableData.push_back(element);
		cin >> element.first;
	}
}

// Prints persons' last names, who has biggest salaries
void outputData(const vector<info> &tableData)
{
	cout << "\nBiggest salaries :" << endl;
	cout << tableData.front().first << endl;
	// While salaries are the same
	for (auto i = tableData.begin(); (*i).second == (*(i + 1)).second; i++) {
		cout << (*(i + 1)).first << endl;
	}
}

// Comparator for 'info'
// Returns true, if elementOne is greater then the second element
// Comparing salaries(snd element of pair). Biggest salaries presented first.
bool infoCompare(const info &elemOne, const info &elemTwo)
{
	return elemOne.second > elemTwo.second;
}

// Sorts pairs, using salary parameter
void sortData(vector<info> &tableData)
{
	sort(tableData.begin(), tableData.end(), infoCompare);
}

int main()
{
	vector<info> table;
	readData(table);
	sortData(table);
	outputData(table);
	return 0;
}