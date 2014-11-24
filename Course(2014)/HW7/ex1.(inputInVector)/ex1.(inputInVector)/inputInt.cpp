#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

void printReverse(const vector<int> &storage)
{
	cout << "\nOutput :" << endl;
	for (auto i = storage.rbegin(); i != storage.rend(); i++) {
		cout << *i << " ";
	}
	cout << endl;
}

int main()
{
	int input;
	vector<int> storage;
	cout << "Input int value sequence (0 for escape) :" << endl;
	cin >> input;
	while (input) {
		storage.push_back(input);
		cin >> input;
	}
	// Output
	printReverse(storage);
	return 0;
}