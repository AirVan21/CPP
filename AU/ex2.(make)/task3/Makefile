FLAGS = -Wall -Werror

all:bin/main

bin/main: bin/main.o bin/add.o bin/a.o
	g++ $(FLAGS) bin/main.o bin/add.o bin/a.o -o bin/main

bin/main.o: src/main.cpp src/add.h src/a.h 
	g++ -c $(FLAGS) src/main.cpp -o bin/main.o

bin/add.o: src/add.cpp src/add.h
	g++ -c $(FLAGS) src/add.cpp -o bin/add.o

bin/a.o: src/a.cpp src/a.h
	g++ -c $(FLAGS) src/a.cpp -o bin/a.o

clean: 
	rm -f bin/*.o main 

.PHONY: clean all