#include "List.h"

List::List() :
	mHead(nullptr),
	mTail(nullptr),
	mLength(0)
{}

void List::append(int inValue)
{
	ListElement *updateHead = new ListElement(inValue);
	if (mLength == 0) {
		mHead = updateHead;
		mTail = updateHead;
	}
	else {
		updateHead->setNext(mHead);
		mHead = updateHead;
	}
	mLength++;
}

void List::push_back(int inValue)
{
	ListElement *updateTail = new ListElement(inValue);
	if (mLength == 0) {
		mHead = updateTail;
		mTail = updateTail;
	}
	else {
		mTail->setNext(updateTail);
		mTail = updateTail;
	}
	mLength++;
}

int List::pop() 
{
	// throw exception
	ListElement *newHead = mHead->getNext();
	int answer = mHead->getValue();
	delete mHead;
	mLength--;
	mHead = newHead;
	return answer;
}

int List::top() const
{
	return mHead->getValue();
}

const ListElement *List::getTail() const
{
	return mTail;
}

const ListElement *List::getHead() const
{
	return mHead;
}

ListElement *List::getTail()
{
	return mTail;
}

ListElement *List::getHead() 
{
	return mHead;
}

void List::addAfterN(int nPos, int inValue)
{
	if (mLength >= nPos) {
		ListElement *additional = new ListElement(inValue);
		ListElement *current = mHead;
		for (int i = 1; i < nPos; i++) {
			current = current->getNext();
		}
		additional->setNext(current->getNext());
		current->setNext(additional);
		mLength++;
	}
}

void List::revertNew()
{
	ListElement *previous = new ListElement(mHead->getValue());
	// Sets new Tail
	mTail = previous;
	ListElement *step = mHead->getNext();
	while (step) {
		ListElement *clone = new ListElement(step->getValue());
		clone->setNext(previous);
		previous = clone;
		step = step->getNext();
	}
	// Head of reverted List now in previous
	while (mHead) {
		step = mHead;
		mHead = mHead->getNext();
		delete step;
	}
	mHead = previous;
}

// Before revert List : x, y, z, w
// After revert  List : w, z, y, x 
void List::revert()
{
	// "Write" List in the end
	ListElement *lastModified = mTail;
	ListElement *step;
	// for all elements befor tail
	for (int i = 1; i < mLength; i++) {
		step = mHead;
		// Gets pre lastModified value
		while (step->getNext() != lastModified) {
			step = step->getNext();
		}
		lastModified->setNext(step);
		lastModified = step;
	}
	mHead = mTail;
	mTail = lastModified;
	mTail->setNext(nullptr);
}

List::~List()
{
	ListElement *help;
	while (mHead) {
		help = mHead;
		mHead = mHead->getNext();
		delete help;
	}
}