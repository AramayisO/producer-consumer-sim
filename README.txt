Running environement: Linux (Fedora 29) x86_64

Compiler: g++  8.2.1 (using C++ 11 threads)

Compile script: g++ --std=c++11 -lpthread -o project1 BBQ.cpp main.cpp

Example run script: ./project1 5000 5000 

General run scritp: ./project1 [max sleep time for producers in milliseconds] [max sleep time for consumers in milliseconds]