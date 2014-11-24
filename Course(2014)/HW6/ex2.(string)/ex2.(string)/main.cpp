#include <iostream>
#include "string.h"

int main()
{
	String s1 = "abc";
	String s2("klm");
	s1 += s2;
	s1.print();
	return 0;
}
