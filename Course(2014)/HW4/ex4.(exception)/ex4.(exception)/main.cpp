#include "time.h"

int main() {
	try {
		Time timer1(33, 13);
	}
	catch (char *str) {
		std::cout << str;
	}
	try {
		Time timer2(13, 99);
	}
	catch (std::exception &exp) {
		std::cout << exp.what() << "\n";
	}
	// timer1.print(); ?
}