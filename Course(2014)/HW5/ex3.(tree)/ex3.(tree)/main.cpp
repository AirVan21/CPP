#include <stdio.h>
#include <iostream>

#include "Tree.h"

using namespace std;

int main()
{
	Tree tree;
	cout << "Print values to add them in tree ( 0 - for exit )\n";
	int input = 0;
	cin >> input;
	while (input)
	{
		tree.add(input);
		cin >> input;
	}
	tree.print();
	return 0;
}