#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> &inputVector, int left, int right)
{
    int index = left;
    int seed = inputVector[index];

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

int findAnswerL(int dot, int index, vector<int> &edges)
{
    while (index < edges.size() && edges[index] <= dot)
        index++;
    return index;
}

void leftBrackets(int dot, int left, int right, vector<int> &edges, int &answer)
{
    if (left <= right)
    {
        int mid = (left + right) / 2;
        if (edges[mid] == dot)
        {
            answer = findAnswerL(dot, mid, edges);
        } 
        else
        {
            if (edges[mid] > dot)
            {
                leftBrackets(dot, left, mid - 1, edges, answer);
            }
            else {
                answer = mid + 1;
                leftBrackets(dot, mid + 1, right, edges, answer);
            }
        }
    }
}

int findAnswerR(int dot, int index, vector<int> &edges)
{
    while (index < edges.size() && edges[index] < dot)
        index++;
    return index;
}

void rightBrackets(int dot, int left, int right, vector<int> &edges, int &answer)
{
    if (left <= right)
    {
        int mid = (left + right) / 2;
        if (edges[mid] == dot)
        {
            answer = findAnswerR(dot, left, edges);
        }
        else
        {
            if (edges[mid] > dot)
            {
                rightBrackets(dot, left, mid - 1, edges, answer);
            }
            else {
                answer = mid + 1;
                rightBrackets(dot, mid + 1, right, edges, answer);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    unsigned int segmentAmount = 0;
    unsigned int dotAmount = 0;

    cin >> segmentAmount;
    cin >> dotAmount;

    vector<int> dotStorage(dotAmount);
    vector<int> leftEdges(segmentAmount);
    vector<int> rightEdges(segmentAmount);

    register int aEdge = 0;
    register int bEdge = 0;

    for (unsigned int i = 0; i < segmentAmount; ++i)
    {
        cin >> aEdge;
        cin >> bEdge;
        leftEdges[i] = aEdge;
        rightEdges[i] = bEdge;
    }

    for (unsigned int i = 0; i < dotAmount; ++i)
    {
        cin >> aEdge;
        dotStorage[i] = aEdge;
    }
    
    qsort(leftEdges, 0, leftEdges.size() - 1);
    qsort(rightEdges, 0, rightEdges.size() - 1);
    
    for (vector<int>::iterator i = dotStorage.begin(); i != dotStorage.end(); i++)
    {
        int leftBracket = 0;
        int rightBracket = 0;
        leftBrackets(*i, 0, leftEdges.size() - 1, leftEdges, leftBracket);
        rightBrackets(*i, 0, rightEdges.size() - 1, rightEdges, rightBracket);
        if (leftBracket - rightBracket > 0) {
            cout << leftBracket - rightBracket << " ";
        }
        else {
            cout << 0 << " ";
        }
    }

    return 0;
}