#include <iostream>
#include <vector>

bool generateNext(int nNum, std::vector<int> &permutation)
{
	int length = (int) permutation.size();
	for (int i = length - 1; i >= 0; i--)
	{ 
		if (permutation[i] < nNum)
		{
			permutation[i]++;
			return true;
		} else {
			if (i - 1 >= 0 && permutation[i - 1] < nNum)
			{
				permutation[i-1]++;
				for (int j = i; j < length; j++)
					permutation[j] = 0;
				return true;
			}
		}
	}
	return false; 
} 

bool isUnique(int nNum, std::vector<int> &permutation)
{
	std::vector<int> flags(nNum);
	for (unsigned int i = 0; i < permutation.size(); i++)
	{
		if (flags[permutation[i]])
		{
			return false;
		}
		else
		{
			flags[permutation[i]] = 1;
		}
	}
	return true; 
}

int main(int argc, char *argv[])
{
	using namespace std;

	int nNum = 0;
	int kNum = 0;
	
	cin >> nNum;
	cin >> kNum;

	vector<int> permutation(kNum);
	
	if (kNum == 1)
		cout << 0 << endl;
	
	while(generateNext(nNum - 1, permutation))
	{
		if (isUnique(nNum, permutation))
		{
			for (vector<int>::iterator pElement = permutation.begin(); pElement != permutation.end(); pElement++)
				cout << *pElement << " ";
			cout << endl;
		}
	}

	return 0;
}