#include "ListElement.h"

ListElement::ListElement(int inValue) :
	mValue(inValue),
	mNext(nullptr)
{}

int ListElement::getValue()
{
	return mValue;
}

void ListElement::setValue(int newValue)
{
	mValue = newValue;
}

ListElement *ListElement::getNext()
{
	return mNext;
}

void ListElement::setNext(ListElement *newNext)
{
	mNext = newNext;
}

ListElement::~ListElement()
{}