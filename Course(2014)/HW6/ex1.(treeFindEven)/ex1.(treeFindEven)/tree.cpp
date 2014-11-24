#include <iostream>
#include "tree.h"

using namespace std;

Tree::Tree(int value) :
	mValue(value),
	mLeftTree(nullptr),
	mRightTree(nullptr)
{}

void Tree::add(Tree* &place, int inValue)
{
	if (place == nullptr) {
		place = new Tree(inValue);
	}
	else
	{
		if (place->mValue > inValue) {
			add(place->mLeftTree, inValue);
		}
		if (place->mValue < inValue) {
			add(place->mRightTree, inValue);
		}
	}
}

void Tree::print(const Tree* tree)
{
	if (tree) {
		print(tree->mLeftTree);
		cout << " " << tree->mValue;
		print(tree->mRightTree);
	}
}

void Tree::findEven(const Tree* tree, bool &answer)
{
	if (tree) {
		if (tree->mValue % 2 == 0) {
			answer = true;
			throw true;
		}
		else {
			findEven(tree->mLeftTree, answer);
			findEven(tree->mRightTree, answer);
		}
	}
}



Tree::~Tree()
{
	delete mLeftTree;
	delete mRightTree;
}