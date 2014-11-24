#include <stdio.h>
#include <iostream>

#include "List.h"

using namespace std;

int main()
{
	// Init
	List list;
	list.append(5);
	list.append(2);
	list.push_back(8);
	
	// Addes 99, after 2nd element in list
	list.addAfterN(2, 99);
	
	// Gets tail element. Squares it's value
	ListElement *last = list.getTail();
	cout << "List tail value = " << last->getValue() << endl;
	last->setValue(last->getValue() * last->getValue());
	cout << "List tail value = " << last->getValue() << endl;
	
	// Reverts elements in list
	// Before : 2 5 99 64
	// After  : 64, 99, 5, 2
	list.revert();

	// Reverts elements in list, creating new L
	// Before : 64, 99, 5, 2
	// After  : 2 5 99 64
	list.revertNew();

	return 0;
}