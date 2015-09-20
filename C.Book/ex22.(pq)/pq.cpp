#include <iostream>
#include <string>
#include <set>
#include <vector> 
#include <algorithm>
#include <queue>

const int ERROR = -1;

struct ListElement
{
    int mValue;
    ListElement* pNext = NULL;

    ListElement(int value) : mValue(value)
    {}
};

struct PriorityList
{
    ListElement *pGuard;

    PriorityList() : pGuard(new ListElement(0))
    {}

    void insert(ListElement *input)
    {
        if (pGuard->pNext == NULL)
        {
            pGuard->pNext = input;
        } else {
            ListElement *pPrev = pGuard;
            ListElement *pCurr = pGuard->pNext;
            while (pCurr != NULL)
            {
                if (pCurr->mValue < input->mValue)
                {
                    pPrev->pNext = input;
                    input->pNext = pCurr;
                    return;
                }
                pPrev = pCurr;
                pCurr = pCurr->pNext;
            }
            pPrev->pNext = input;
        }
    }

    int extractMax()
    {
        if (pGuard->pNext != NULL)
        {
            int answer = pGuard->pNext->mValue;
            ListElement *nextHead = pGuard->pNext->pNext;
            delete pGuard->pNext;
            pGuard->pNext = nextHead;
            return answer;
        }
        return ERROR;
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;
    int nOperation = 0;
    cin >> nOperation;
    PriorityList list;
    
    for (int i = 0; i < nOperation; ++i)
    {
        string command;
        cin >> command;
        if (command == "Insert")
        {
            int nNum = 0;
            cin >> nNum;
            ListElement *pNewElement = new ListElement(nNum);
            list.insert(pNewElement);
        }

        if (command == "ExtractMax")
        {
            cout << list.extractMax() << endl;
        }
    }

    return 0;
}