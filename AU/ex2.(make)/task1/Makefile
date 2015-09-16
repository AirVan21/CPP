FLAGS = -Werror -Wall

all:bin/main

bin/main: bin/main.o bin/add.o
	g++ $(FLAGS) bin/main.o bin/add.o -o bin/main

bin/main.o: src/main.cpp
	g++ -c $(FLAGS) src/main.cpp -o bin/main.o

bin/add.o: src/add.cpp
	g++ -c $(FLAGS) src/add.cpp -o bin/add.o

clean: 
	rm bin/*.o

.PHONY: clean all