// Represents node of Tree class
class TreeElement
{

public:
	// Constructor
	// @param value main parameter
	TreeElement(int value);
	~TreeElement();
	
	// Gets data from TreeElement's fields
	int getValue();
	TreeElement *getLeftSon();
	TreeElement *getRightSon();
	
	// Sets data in TreeElement's fields
	void setValue(int newValue);
	void setLeftSon(TreeElement *son);
	void setRightSon(TreeElement *son);


private:
	int mValue;
	// Pointer to son with less value
	TreeElement *mLeftSon;
	// Pointer to son with greater value
	TreeElement *mRightSon;

};