#include <iostream>


int fibon(int n)
{
	int nFirstNum = 0;
	int nSecondNum = 1;
	
	if (n == 0)
		return nFirstNum;
	if (n == 1)
		return nSecondNum;
	
	int nHelp = 0;
	
	for (int i = 1; i < n; i++)
	{
		nHelp = (nFirstNum + nSecondNum);
		nFirstNum = nSecondNum;
		nSecondNum = nHelp;
	}

	return nSecondNum;
}

int main(int argc, char *argv[])
{
	using namespace std;
	
	int nInput = 0;
	cin >> nInput;
	cout << fibon(nInput);

	return 0;
}