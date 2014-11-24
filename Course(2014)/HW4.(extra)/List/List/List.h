#pragma once

#include "ListElement.h"

// Represents List model
class List
{

public:
	// Constructor
	List();
	~List();
	// Addes value to the start of the List
	void append(int inValue);
	// Addes value to the end of the List
	void push_back(int inValue);
	// Takes mHead int value
	int top() const;
	// Takes mHead int value & Removes mHead from List
	int pop();
	// Gets tail pointer
	const ListElement *getTail() const;
	// Gets head pointer
	const ListElement *getHead() const;
	// Gets tail pointer
	ListElement *getTail();
	// Gets head pointer
	ListElement *getHead();
	// Adds "inValue" to the list, after element in "inPos" position
	// If nPos > list.mLength => ignore addition
	void addAfterN(int nPos, int inValue);
	// Reverts list
	void revert();
	// Reverst list, creating new elements
	void revertNew();

private:
	// Note List's head
	ListElement *mHead;
	// Note List's tail
	ListElement *mTail;
	// List length
	int mLength;

};
