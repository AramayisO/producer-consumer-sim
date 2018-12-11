CC=g++
CFLAGS=--std=c++11 -lpthread

main: BBQ.cpp BBQ.h main.cpp
	$(CC) -o main BBQ.cpp main.cpp $(CFLAGS)