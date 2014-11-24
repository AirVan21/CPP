#include "Tree.h"

Tree::Tree() : 
	mRoot(nullptr)
{}

void Tree::add(int newValue)
{
	if (!mRoot) {
		mRoot = new TreeElement(newValue);
	} 
	else {
		if (newValue > mRoot->getValue()) {
			addRecRight(mRoot->getRightSon(), mRoot, newValue);
		}
		if (newValue < mRoot->getValue()) {
			addRecLeft(mRoot->getLeftSon(), mRoot, newValue);
		}
	}
}

void Tree::addRecLeft(TreeElement *place, TreeElement *parent, int valueToAdd)
{
	if (!place) {
		TreeElement *node = new TreeElement(valueToAdd);
		parent->setLeftSon(node);
	}
	else {
			if (valueToAdd > place->getValue()) {
				addRecRight(place->getRightSon(), place, valueToAdd);
			}
			if (valueToAdd < place->getValue()) {
				addRecLeft(place->getLeftSon(), place, valueToAdd);
			}
	}
}

void Tree::addRecRight(TreeElement *place, TreeElement *parent, int valueToAdd)
{
	if (!place) {
		TreeElement *node = new TreeElement(valueToAdd);
		parent->setRightSon(node);
	}
	else {
		if (valueToAdd > place->getValue()) {
			addRecRight(place->getRightSon(), place, valueToAdd);
		}
		if (valueToAdd < place->getValue()) {
			addRecLeft(place->getLeftSon(), place, valueToAdd);
		}
	}
}

void Tree::print()
{
	std::cout << "Prints tree :\n";
	printRec(mRoot); 
	std::cout << std::endl;
}

void Tree::printRec(TreeElement *place)
{
	if (place) {
		std::cout << " " << place->getValue();
		printRec(place->getLeftSon());
		printRec(place->getRightSon());
	}
}

Tree::~Tree()
{}