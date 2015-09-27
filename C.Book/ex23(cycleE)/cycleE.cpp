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

    // Init identity table
    vector< vector<int> > mGraph(nVerteces, vector<int>(nVerteces));

    for (unsigned int i = 0; i < nEdges; ++i)
    {
        cin >> aNode;
        cin >> bNode;
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