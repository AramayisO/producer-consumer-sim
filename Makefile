CC=g++
CFLAGS=--std=c++11 -lpthread

main: BBQ.cpp Producer.cpp Consumer.cpp main.cpp
	$(CC) -o main BBQ.cpp Producer.cpp Consumer.cpp main.cpp $(CFLAGS)

clean:
	rm main
	rm *.o