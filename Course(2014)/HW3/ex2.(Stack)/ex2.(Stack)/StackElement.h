class StackElement {

public:
	
	StackElement(int value );

	int& getValue();

	void setNext(StackElement *nextIn);

	StackElement *getNext();

private:

	int value;

	StackElement *next;
};