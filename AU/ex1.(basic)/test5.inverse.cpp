#include <iostream>
#include <string>


void inverseStr(std::string &inputStr, std::string &outputStr)
{
	int length = (int) inputStr.size();
	for (int i = length - 1; i >= 0; i--)
	{
		outputStr = outputStr + inputStr[i];
	}
}

int main(int argc, char* argv[])
{
	using std::string;
	using std::cin;
	using std::cout;

	string input;
	cin >> input;

	string outputStr = "";
	inverseStr(input, outputStr);
	cout << outputStr;

	return 0; 
}