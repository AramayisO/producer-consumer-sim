CC=g++
CFLAGS=--std=c++11 -lpthread -O2
WARN=-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
DEF=-DFIXED_NUMBER_OF_ITERATIONS

main: BBQ.cpp Producer.cpp Consumer.cpp main.cpp
	$(CC) -o main BBQ.cpp Producer.cpp Consumer.cpp main.cpp $(CFLAGS) $(WARN)

fixed-iter: BBQ.cpp Producer.cpp Consumer.cpp main.cpp
	$(CC) -o main BBQ.cpp Producer.cpp Consumer.cpp main.cpp $(CFLAGS) $(WARN) $(DEF)

clean:
	rm main