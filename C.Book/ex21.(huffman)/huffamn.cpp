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
    int  mStatistics;
    Tree* leftSon = NULL;
    Tree* rightSon = NULL;

    Tree(char value, int statistics)
    {
        mValue = value;
        mStatistics = statistics;
    } 
};

class CompareTree
{
public:
    bool operator()(Tree *tr1, Tree *tr2)
    {
        return tr1->mStatistics > tr2->mStatistics;
    }
};

void generateCode(Tree *tree, char letter, string way)
{
    if (tree != NULL)
    {
        cout << tree->mValue << endl;
        generateCode(tree->leftSon, letter, way);
    }
}

void printQueue(priority_queue<Tree*, vector<Tree*>, CompareTree> pq)
{
    while(!pq.empty())
    {
        Tree *qElem = pq.top();
        pq.pop();
        cout << qElem->mValue << " " << qElem->mStatistics << endl;
    }
}

int main(int argc, char const *argv[])
{
    string inputStr;
    cin >> inputStr;
    set<char> uniqueLetters;
    
    for (unsigned int i = 0; i < inputStr.length(); ++i)
        uniqueLetters.insert(inputStr[i]);

    vector< pair<char,int> > letters;
    
    for (set<char>::iterator i = uniqueLetters.begin(); i != uniqueLetters.end(); ++i)
        letters.push_back(make_pair(*i, 0));

    for (unsigned int i = 0; i < inputStr.length(); ++i)
    {
        for (unsigned int j = 0; j < letters.size(); ++j)
        {
            if (letters[j].first == inputStr[i])
            {
                letters[j].second++;
                break;
            }
        }
    }

    priority_queue<Tree*, vector<Tree*>, CompareTree> priorityQueue;
    for (unsigned int i = 0; i < letters.size(); i++)
    {
        Tree *letterLeaf = new Tree(letters[i].first, letters[i].second);
        priorityQueue.push(letterLeaf);
    }
    
    vector<Tree*> nodes;

    while (priorityQueue.size() > 1)
    {
        Tree *element1 = priorityQueue.top();
        priorityQueue.pop();
        //Tree *minFirst = new Tree(element->mValue, element->mStatistics);
        nodes.push_back(element1);
        
        Tree *element2 = priorityQueue.top();
        priorityQueue.pop();
        //Tree *minSecond = new Tree(element->mValue, element->mStatistics);
        nodes.push_back(element2);
        
        Tree *extraNode = new Tree('@', element1->mStatistics + element2->mStatistics);
        extraNode->leftSon  = element1;
        extraNode->rightSon = element2;
        priorityQueue.push(extraNode);
    }

    Tree *root = priorityQueue.top();
    vector<string> code(letters.size());
    for (unsigned int i = 0; i < letters.size(); ++i)
    {
        char letter = letters[i].first;
        generateCode(root, letter, "");
        //cout << letter << ":" << code;
    }

    /*
    for (unsigned i = 0; i < inputStr.length(); i++)
    {
        for (unsigned int j = 0; j < letters.size(); ++j)
        {
            if (letters[j].first == inputStr[i])
            {
                //result = result + code[j];
                break;
            }
        }
    }

    // Output
    //cout << uniqueLetters.size() << " " << result.length() << endl;
    for (unsigned int i = 0; i < letters.size(); i++)
        cout << letters[i].first << ":" << endl;
    */

    return 0;
}