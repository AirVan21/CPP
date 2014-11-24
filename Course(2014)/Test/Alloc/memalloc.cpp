#include <stdio.h>
#include <time.h>

#define SIZE 1024*100

int main(void) {
	char *p = NULL;
	while (true) {
		p = malloc(SIZE);
		if(p) {
			printf("Alloc %s\n", SIZE);
		} else {
			printf("Fail!\n");
		}
	}
	return 0;
}