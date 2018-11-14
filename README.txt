Running environement: Linux (Fedora 29) x86_64

Compiler: g++  8.2.1 (using C++ 11 threads)

Compile script: g++ --std=c++11 -lpthread -o main TSQueue.cpp main.cpp

Example run script: ./main 5000 5000 

General run scritp: ./main [max sleep time for producers in milliseconds] [max sleep time for consumers in milliseconds]