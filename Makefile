# Makefile

all: runMovies

runMovies: main.o movies.o
	g++ --std=c++11 -g -o runMovies main.cpp movies.o

main.o: main.cpp
	g++ -c -g --std=c++11 main.cpp

movies.o: movies.cpp
	g++ -c -g --std=c++11 movies.cpp

clean:
	rm -f runMovies *.o
