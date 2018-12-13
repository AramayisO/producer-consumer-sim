Running environement: Linux (Fedora 29) x86_64

Compiler: g++  8.2.1 (using C++ 11 threads)

Compile script: g++ -o project1 BBQ.cpp Producer.cpp Consumer.cpp main.cpp --std=c++11 -lpthread -O2

Example run script: ./project1 5000 5000 

General run scritp: ./project1 [max sleep time for producers in milliseconds] [max sleep time for consumers in milliseconds]