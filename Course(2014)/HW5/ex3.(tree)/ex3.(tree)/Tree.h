#pragma once
#include <iostream>

#include "TreeElement.h"

// Represents binary tree
class Tree
{

public:
	// Constructor
	Tree();
	~Tree();

	// Adds new element, keeping tree sorted
	void add(int newValue);
	// Print values in tree nodes
	void print();


private:
	//  Recursive add
	void addRecLeft(TreeElement *place, TreeElement *parent, int valueToAdd);
	void addRecRight(TreeElement *place, TreeElement *parent, int valueToAdd);
	// Recourcive detour
	void printRec(TreeElement *place);

	// Tree root
	TreeElement *mRoot;

};

