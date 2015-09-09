#include <iostream>

int main(int argc, char* argv[])
{
	using std::cout;
	using std::cin;
	using std::endl;

	const int inputSize = 5;

	double inputNum = 0;
	double sum = 0;

	for (int i = 0; i < inputSize; i++)
	{
		cout << "Input (" << i + 1 << ") = ";
		cin >> inputNum;
		sum += inputNum;
	}

	double average = sum / inputSize;
	cout << "Result = " << average << endl;

	return 0; 
}