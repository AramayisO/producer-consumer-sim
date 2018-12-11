CC=g++
CFLAGS=--std=c++11 -lpthread

main: BBQ.cpp Producer.cpp main.cpp
	$(CC) -o main BBQ.cpp Producer.cpp main.cpp $(CFLAGS)

clean:
	rm main
	rm *.o