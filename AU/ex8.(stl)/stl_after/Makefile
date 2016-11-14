FLAGS = -std=c++14 -Wall -Werror
CC = g++

all: stl_practice

stl_practice: main.o
	$(CC) $(FLAGS) main.o -o stl_practice

main.o: main.cpp stl_practice.h
	$(CC) $(FLAGS) -c main.cpp -o main.o

.PHONY: all clean

clean:
	rm *.o stl_practice