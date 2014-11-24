// Representation for binary tree
class Tree
{
public:
	Tree(int value);
	~Tree();
	// Adds element
	void add(Tree* &place, int value);
	// Returns true if tree has even value
	void findEven(const Tree* tree, bool &answer);
	// Prints tree elements
	void print(const Tree *tree);

private:
	int mValue;
	// Left SubTree
	Tree *mLeftTree;
	// Right SubTree
	Tree *mRightTree;

	void clear(Tree *tree);
};

