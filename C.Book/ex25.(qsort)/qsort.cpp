#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int nEntries = 0;

int partition(vector<int> &inputVector, int left, int right)
{
    int index = left;
    int seed  = inputVector[index];

    for (int i = left + 1; i <= right; i++)
    {
        if (inputVector[i] <= seed)
        {
            index++;
            swap(inputVector[i], inputVector[index]);
        }
    }

    swap(inputVector[left], inputVector[index]);

    return index;
}

void qsort(vector<int> &inputVector, int leftEdge, int rightEdge)
{
    if (leftEdge < rightEdge)
    {
        int mid = partition(inputVector, leftEdge, rightEdge);
        qsort(inputVector, leftEdge, mid - 1);
        qsort(inputVector, mid + 1, rightEdge);
    }
}

int pairPartition(vector< pair<int, int> > &inputVector, int left, int right);

void qSortPair(vector< pair<int, int> > &inputVector, int left, int right)
{
    if (left < right)
    {
        int mid = pairPartition(inputVector, left, right);
        qSortPair(inputVector, left, mid - 1);
        qSortPair(inputVector, mid + 1, right);
    }
}

int pairPartition(vector< pair<int, int> > &inputVector, int left, int right)
{
    int index = left;
    int seed = inputVector[index].first;

    for (int i = left + 1; i <= right; i++)
    {
        if (inputVector[i].first <= seed)
        {
            index++;
            swap(inputVector[i], inputVector[index]);
        }
    }
    swap(inputVector[index], inputVector[left]);
    return index;
}

bool inSegment(int dot, pair<int, int> &segment)
{
    return (dot >= segment.first) && (dot <= segment.second); 
}

int wideSearch(int dot, int index, vector< pair<int, int> > segmentVector)
{
    int nAmount = 0;
    int i = index - 1;
    int j = index + 1;
    while (i >= 0 && inSegment(dot, segmentVector[i]))
    {
        nAmount++;
        i--;
    }
    while (j < segmentVector.size() && inSegment(dot, segmentVector[j]))
    {
        nAmount++;
        j++;
    }
    return nAmount;
}

void entriesInVector(int dot, vector< pair<int, int> > segmentVector, int left, int right)
{
    int mid = (left + right) / 2; 

    if (inSegment(dot, segmentVector[mid]))
    {
        nEntries++;
        nEntries += wideSearch(dot, mid, segmentVector);
    } else {
        if (dot < segmentVector[mid].first)
        {
            entriesInVector(dot, segmentVector, left, mid - 1);
        } 
        else if (dot > segmentVector[mid].second) 
        {
            entriesInVector(dot, segmentVector, mid + 1, right);
        }  
    }
}

int main(int argc, char const *argv[])
{
    unsigned int segmentAmount = 0;
    unsigned int dotAmount = 0;
    
    cin >> segmentAmount;
    cin >> dotAmount;
    
    vector< pair<int, int> > segmentStorage(segmentAmount);
    vector<int> dotStorage(dotAmount);
    
    register int aEdge = 0;
    register int bEdge = 0;

    for (unsigned int i = 0; i < segmentAmount; ++i)
    {
        cin >> aEdge;
        cin >> bEdge;
        segmentStorage[i] = make_pair(aEdge, bEdge);
    }

    for (unsigned int i = 0; i < dotAmount; ++i)
    {
        cin >> aEdge;
        dotStorage[i] = aEdge;
    }

    qsort(dotStorage, 0, (dotStorage.size()-1));
    qSortPair(segmentStorage, 0, segmentStorage.size() - 1);
    entriesInVector(dotStorage[1], segmentStorage, 0, segmentStorage.size() - 1);
    cout << nEntries << endl;
        
    /*
    for (vector<int>::iterator i = dotStorage.begin(); i != dotStorage.end(); i++)
    {
        entriesInVector(*i, segmentStorage, 0, segmentStorage.size() - 1);
        cout << nEntries << endl;
        nEntries = 0;
    }
    */

    return 0;
}