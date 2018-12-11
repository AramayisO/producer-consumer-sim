CC=g++
CFLAGS=--std=c++11 -lpthread
WARN=-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

main: BBQ.cpp Producer.cpp Consumer.cpp main.cpp
	$(CC) -o main BBQ.cpp Producer.cpp Consumer.cpp main.cpp $(CFLAGS) $(WARN)

clean:
	rm main