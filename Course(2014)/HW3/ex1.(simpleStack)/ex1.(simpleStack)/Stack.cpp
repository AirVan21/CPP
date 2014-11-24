#include "Stack.h"

Stack::Stack() : 
	length(0)
	, top(source)
{}

void Stack::push(int param)
{
	if (length < 100) {
		*top = param;
		top++;
		length++;
	} else {
		std::cout << "Houston, we've had a problem\n";
	}
}

int Stack::pop()
{
	int answer = 0;

	if (length) {
		top--;
		length--;
		answer = *top;
		return answer;
	} else {
		std::cout << "Houston, we've had a problem\n";
		return -1;
	}
}
