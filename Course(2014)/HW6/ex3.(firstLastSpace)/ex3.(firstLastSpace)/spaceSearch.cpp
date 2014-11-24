#include <iostream>

using namespace std;

int firstSpace(const char *string) {
	int place = 1;
	const char *i = string;
	for (; *i != ' ' && *i != '\0'; i++) {
		place++;
	}
	if (*i == '\0') {
		throw "No spaces in a string!";
	}
	return place;
}

int lastSpace(const char *string) {
	int place = strlen(string);
	// Sets on last char != '\0'
	const char *i = string + place - 1;
	for (; *i != ' ' && place > 0; i--) {
		place--;
	}
	return place;
}

const int dimension = 100;

int main() {

	char string[dimension];
	cout << "Input you string:\n";
	char delimeter = '\n';
	cin.getline(string, dimension, delimeter);
	try{
		int first = firstSpace(string);
		int last = lastSpace(string);
		cout << "First space position = " << first << endl;
		cout << "Last  space position = " << last << endl;
	}
	catch (char *msg) {
		cout << msg << endl;
	}
	return 0;
}

