#include <iostream>

/*
	nFib   - (order number of Fibonacci number)
	module - divider
*/
long long fibPerModule(long long nFib, long long module)
{
	if (nFib < 3)
		return 1;

	/*
		a, b  0 1
		c, d  1 1 
	*/

	register long long nFibA = 0;
	register long long nFibB = 1;
	register long long nFibC = 1;
	register long long nFibD = 1;

	long long temp = 0;
	long long tempA, tempB , tempC;
	tempA = tempB = tempC = 0;

	long long nFibX = 0;
	long long nFibY = 1;
	
	while(nFib)
	{
		if (nFib & 1)
		{
			temp = nFibX;
			nFibX = (nFibX * nFibA + nFibY * nFibC) % module;
			nFibY = (temp * nFibB + nFibY * nFibD) % module;
		}
		
		tempA = nFibA; tempB = nFibB; tempC = nFibC; 
		
		nFibA = (nFibA * nFibA + nFibB * nFibC) % module;
		nFibB = (tempA * nFibB + nFibB * nFibD) % module;
		nFibC = (tempA * nFibC + nFibC * nFibD) % module;
		nFibD = (tempB * tempC + nFibD * nFibD) % module;

		nFib >>= 1;
	}

	return nFibX;
}

int main(int argc, char *argv[])
{
	using namespace std;
	long long fibOrder = 0;
	long long module = 0;

	cin >> fibOrder;
	cin >> module;

	cout << fibPerModule(fibOrder, module);

	return 0;
}