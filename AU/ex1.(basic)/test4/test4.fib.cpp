#include <iostream>
#include <fstream>
#include <vector>

int fib(int n)
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

int main(int argc, char* argv[])
{
	using namespace std;

	ifstream input("input.txt");
	ofstream output("output.txt");

	int nOrder = 0;
	input >> nOrder;
	output << fib(nOrder);

	return 0; 
}