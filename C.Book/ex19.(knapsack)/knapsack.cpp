#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void printPairVector(vector< pair<int, double> > &inputVector)
{
	for (unsigned int i = 0; i < inputVector.size(); i++)
		cout << inputVector[i].first << " " << inputVector[i].second << endl;
	cout << endl;
}

bool pairComparator(pair<int, double> aPair, pair<int, double> bPair)
{
	return aPair.second >= bPair.second;
}

int main(int argc, char const *argv[])
{
	using namespace std;
	unsigned int nObjects =  0;
	int nCapacity = 0;
	
	cin >> nObjects;
	cin >> nCapacity;

	double nValue  = 0;
	int    nWeight = 0;

	vector< pair<int, double> > catalogList; 

	for (unsigned int i = 0; i < nObjects; ++i)
	{
		cin >> nValue;
		cin >> nWeight;
		catalogList.push_back(make_pair(nWeight, nValue / (double) nWeight));
	}

	sort(catalogList.begin(), catalogList.end(), pairComparator);
	
	double nCash = 0;

	for (size_t i = 0; i < catalogList.size(); ++i)
	{
		if (nCapacity >= catalogList[i].first)
		{
			nCapacity -= catalogList[i].first;
			nCash += catalogList[i].first * catalogList[i].second; 
		} 
		else {
			nCash += nCapacity * catalogList[i].second;
			break; 
		}
	}

	printf("%.3f\n", nCash);

	return 0;
}