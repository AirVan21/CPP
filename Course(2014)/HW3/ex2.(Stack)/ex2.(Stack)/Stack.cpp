#include "Stack.h"

Stack::Stack() : 
	top(nullptr),
	zero(0),
	accum(1)
{}

void Stack::push(int param)
{
	StackElement *element = new StackElement(param);
	auto help = top;
	element->setNext(help);
	top = element;
	
	if (param) {
		accum *= param;
	} else {
		zero++;
	}
}

int Stack::pop()
{
	if (top != nullptr) {
		int answer = top->getValue();
		top = top->getNext();
		if (answer) {
			accum /= answer;
		} else {
			zero--;
		}
		return answer;
	} else {
		return -1;
	}
}

long Stack::product()
{
	return zero ? 0 : accum;
}

int& Stack::topStack()
{
	return top->getValue();
}
