#include <iostream>
#include <string>
#include <set>
#include <vector> 
#include <algorithm>

void findEulerCycle()
{

}

int main(int argc, char const *argv[])
{
    using namespace std;

    int nVerteces = 0;
    unsigned int nEdges = 0;
    
    cin >> nVerteces;
    cin >> nEdges;
    
    int aNode = 0;
    int bNode = 0;

    vector< vector<int> > mGraph(nVerteces);
    vector< pair<int, int> > mEdges;
    for (unsigned int i = 0; i < nEdges; ++i)
    {
        cin >> aNode;
        cin >> bNode;
        mGraph[aNode - 1].push_back(bNode - 1);
        mGraph[bNode - 1].push_back(aNode - 1);
        mEdges.push_back(make_pair(aNode - 1, bNode -1));
    }

    for (unsigned int i = 0; i < nEdges; ++i)
    {
        if (mGraph[i].size() % 2 != 0)
        {
            cout << "NONE" << endl;
            return 0;
        }
    }
    
    findEulerCycle();

    return 0;
}