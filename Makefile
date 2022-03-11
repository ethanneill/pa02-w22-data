# Makefile

all: runMovies

runMovies: main.o movies.o
	g++ --std=c++11 -Wall -g -o runMovies main.cpp movies.o

main.o: main.cpp
	g++ -c -g --std=c++11 -Wall main.cpp

movies.o: movies.cpp
	g++ -c -g --std=c++11 -Wall movies.cpp

clean:
	rm -f runMovies *.o
