#include <iostream>
#include <vector>

// Default const
#define OK 0

// Namespace <std> include
using std::cout;
using std::endl;

using std::pair;
using std::vector; 
 
int main() 
{
	// Create test values
	pair<double, double> element1(4, 5.5);
	pair<double, double> element2(1, 0);
	// Storage
	vector< pair<double, double> > listOfPair;
	// Insert into vector
	listOfPair.push_back(element1); 
	listOfPair.push_back(element2);
	listOfPair.push_back(std::make_pair(2,4));

	unsigned int counter = 0;
	// Test foreach
	for (auto &pairEl : listOfPair) {
		cout << ++counter << " : " << "("<< pairEl.first  << "; " << pairEl.second << ")"<< endl;
	}

	return 0;
}
