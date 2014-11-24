#include <string.h>
#include <iostream>

#include "string.h"

using namespace std;

String::String(const char *word) : 
	mLength(strlen(word))
{
	pString = new char[mLength + 1];
	strcpy_s(pString, mLength + 1, word);
}

String::String(const String &word) :
mLength(word.mLength)
{
	pString = new char[mLength + 1];
	strcpy_s(pString, mLength + 1, word.pString);
}

String &String::operator=(const char *word)
{
	mLength = strlen(word);
	delete[] pString;
	// +1 for \o symbol
	pString = new char[mLength + 1];
	strcpy_s(pString, mLength + 1, word);
	return *this;
}

String &String::operator=(const String &word)
{
	if (this != &word)
		*this = word.pString;
	return *this;
}

String &String::operator+=(const String &word)
{
	int resLength = mLength + word.mLength + 1;
	// Concatenation result
	char *result = new char[resLength];
	strcpy_s(result, mLength + 1, pString);
	strcpy_s(result + mLength, word.mLength + 1, word.pString);
	delete[] pString;
	pString = result;
	mLength = --resLength;
	return *this;
}

void String::print()
{
	for (char *i = pString; *i != '\0'; i++) {
		cout << *i;
	}
	cout << endl;
}

String::~String()
{
	// delete for char array
	delete[] pString;
}