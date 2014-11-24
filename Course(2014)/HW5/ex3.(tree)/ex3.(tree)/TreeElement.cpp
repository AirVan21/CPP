#include "TreeElement.h"

TreeElement::TreeElement(int value) : 
	mValue(value),
	mLeftSon(nullptr),
	mRightSon(nullptr)
{}

int TreeElement::getValue() 
{
	return mValue;
}

TreeElement *TreeElement::getLeftSon()
{
	return mLeftSon;
}

TreeElement *TreeElement::getRightSon()
{
	return mRightSon;
}

void TreeElement::setValue(int newValue)
{
	mValue = newValue; 
}

void TreeElement::setLeftSon(TreeElement *son)
{
	mLeftSon = son;
}

void TreeElement::setRightSon(TreeElement *son)
{
	mRightSon = son;
}

TreeElement::~TreeElement()
{}

