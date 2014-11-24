#include "StackElement.h"

StackElement::StackElement(int value) :
	value(value)
	,next(nullptr)
{}

int& StackElement::getValue()
{
	return value;
}

void StackElement::setNext(StackElement *nextIn)
{
	next = nextIn;
}

StackElement *StackElement::getNext()
{
	return next;
}