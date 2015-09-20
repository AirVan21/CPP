#include <iostream>
#include <string>
#include <set>
#include <vector> 
#include <algorithm>
#include <queue>

using namespace std;


class Comparator
{
public:
    bool operator()(int numA, int numB)
    {
        return numA < numB;
    }
};


int main(int argc, char const *argv[])
{
    using namespace std;
    priority_queue<int, vector<int>, Comparator> priorityQueue;
    
    int nOperation = 0;
    cin >> nOperation;
    
    for (int i = 0; i < nOperation; ++i)
    {
        string command;
        cin >> command;
        if (command == "Insert")
        {
            int nNum = 0;
            cin >> nNum;
            priorityQueue.push(nNum);
        }

        if (command == "ExtractMax")
        {
            cout << priorityQueue.top() << endl;
            priorityQueue.pop();
        }
    }
    return 0;
}