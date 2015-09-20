#include <iostream>
#include <cstdio>
#include <vector> 

using namespace std;

int main(int argc, char const *argv[])
{
	int nNum = 0;
	int kNum = 0;
	int nSum = 0;
	int nLast = 0;
	vector<int> out;
	cin >> nNum;

	while ((nNum - nSum) / 2 > ++kNum)	
	{		
		out.push_back(kNum);
		nLast = kNum;
		nSum += kNum;
	}

	if ((nNum - nSum) / 2 != nLast && kNum < (nNum - nSum - kNum))
	{
		out.push_back(kNum);
		nSum += kNum;	
	}
	
	out.push_back(nNum - nSum);
	

	cout << out.size() << endl;

	for (size_t i = 0; i < out.size(); i++)
	{
		cout << out[i] << " ";
	}
	cout << endl;

	return 0;
}