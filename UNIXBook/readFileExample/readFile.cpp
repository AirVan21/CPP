#include <stdio.h>
#include <iostream>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define OK 0

const int bufSize = 100;

int main()
{
	int fd = 0;
	char buf[bufSize];
	// Open File
	fd = open("../../README.md", O_RDONLY);
	// Read in Buffer
	read(fd, buf, sizeof(buf));
	// Close File
	(void)close(fd);
	// Print first 10 chars
	for (int i = 0; i < 10; i++) {
		std::cout << buf[i];
	}
	std::cout << "\n";
	return OK;
}