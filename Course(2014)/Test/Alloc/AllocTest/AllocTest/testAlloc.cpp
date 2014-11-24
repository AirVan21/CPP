#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024*100

int main(void) {
	while (true) {
		malloc(SIZE);
		printf("Alloc %s\n", SIZE);
	}
	return 0;
}