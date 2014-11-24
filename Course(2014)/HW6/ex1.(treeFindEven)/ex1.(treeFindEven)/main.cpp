#include <stdio.h>
#include <iostream>

#include "tree.h"

using namespace std;

int main()
{
	Tree *tree = new Tree(5);
	bool hasEven = false;
	tree->add(tree, 5);
	tree->add(tree, 7);
	tree->add(tree, 11);
	tree->add(tree, 1);
	tree->add(tree, 3);
	tree->add(tree, 8);
	tree->print(tree);
	try {
		tree->findEven(tree, hasEven);
	} catch (bool found) {
		cout << "\n Has even value!\n" << endl;
	}
	delete tree;
	return 0;
}