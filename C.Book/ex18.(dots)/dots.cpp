#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printPairVector(vector< pair<int, int> > &inputVector)
{
	for (unsigned int i = 0; i < inputVector.size(); i++)
		cout << inputVector[i].first << " " << inputVector[i].second << endl;
	cout << endl;
}

void printVector(vector<int> &inputVector)
{
	for (unsigned int i = 0; i < inputVector.size(); i++)
		cout << inputVector[i] << " ";
	cout << endl;
}

bool pairComparator(pair<int, int> aPair, pair<int, int> bPair)
{
	return aPair.second <= bPair.second;
}

bool isIn(int dot, pair<int,int> &pair)
{
	return (pair.first <= dot) && (dot <= pair.second);
}

int main(int argc, char const *argv[])
{
	int nAmount = 0;
	cin >> nAmount;
	
	int aEdge = 0;
	int bEdge = 0;

	vector< pair< int,int > > segmentVector;

	for (int i = 0; i < nAmount; ++i)
	{
		cin >> aEdge;
		cin >> bEdge;
		segmentVector.push_back(make_pair(aEdge, bEdge));
	}

	sort(segmentVector.begin(), segmentVector.end(), pairComparator);

	vector<int> dots;
	int testPoint = segmentVector[0].second;
	dots.push_back(testPoint);
	for (unsigned int i = 1; i < segmentVector.size(); i++)
	{
		if (!isIn(testPoint, segmentVector[i]))
		{
			testPoint = segmentVector[i].second;
			dots.push_back(testPoint);
		}
	}

	cout << dots.size() << endl;
	printVector(dots);
	//printPairVector(segmentVector);

	return 0;
}