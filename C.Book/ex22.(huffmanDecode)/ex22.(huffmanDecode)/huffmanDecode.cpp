#include <iostream>
#include <string>
#include <set>
#include <vector> 
#include <algorithm>
#include <queue>

using namespace std;

struct Tree
{
	char mValue;
	Tree* leftSon = NULL;
	Tree* rightSon = NULL;

	Tree(char value)
	{
		mValue = value;
	}

	void add(Tree *tree, char symbol, string &code, int index)
	{
		if (tree != NULL)
		{
			if (index == code.length())
			{
				tree->mValue = symbol;
			} else {
				if (code[index] == '0')
				{
					if (tree->leftSon != NULL)
					{
						++index;
						add(tree->leftSon, symbol, code, index);
					} else {
						++index;
						Tree *subTree = new Tree('@');
						tree->leftSon = subTree;
						add(tree->leftSon, symbol, code, index);
					}
				} else {
					if (tree->rightSon != NULL)
					{
						++index;
						add(tree->rightSon, symbol, code, index);
					} else {
						++index;
						Tree *subTree = new Tree('@');
						tree->rightSon = subTree;
						add(tree->rightSon, symbol, code, index);
					}
				}
			}
		}
	}

	void decodeNext(Tree *tree, string &input, int &index)
	{
		if (index <= input.size())
		{
			if (tree->leftSon == NULL && tree->rightSon == NULL)
			{
				cout << tree->mValue;
			}
			else {
				if (input[index] == '0')
				{
					index++;
					decodeNext(tree->leftSon, input, index);
				} else {
					index++;
					decodeNext(tree->rightSon, input, index);
				}
			}
		}
	}
};

int main(int argc, char const *argv[])
{
	vector<pair<char, string>> codeTable;
	int nAlphabet = 0;
	int nString = 0;
	string mainCode = "";
	cin >> nAlphabet;
	cin >> nString;
	
	for (unsigned int i = 0; i < nAlphabet; ++i)
	{
		string symbol = "";
		string inCode = "";
		cin >> symbol;
		cin >> inCode;
		codeTable.push_back(make_pair(symbol[0], inCode));
	}

	cin >> mainCode;
	
	Tree *root = new Tree('@');
	for (size_t i = 0; i < codeTable.size(); ++i)
	{
		root->add(root, codeTable[i].first, codeTable[i].second, 0);
	}

	int counter = 0;
	while (counter < nString)
	{
		root->decodeNext(root, mainCode, counter);
	}
		
	return 0;
}