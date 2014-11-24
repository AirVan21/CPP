// Represents the element of List class
class ListElement
{

public:
	// Constructor
	ListElement(int inValue);

	~ListElement();

	// Takes mValue
	int getValue();
	// Sets mValue
	void setValue(int newValue);
	// Takes mNext
	ListElement *getNext();
	// Sets mNext
	void setNext(ListElement *newNext);

private:
	// Useful data
	int mValue;
	// Pointer to the next element in List
	ListElement *mNext;

};
