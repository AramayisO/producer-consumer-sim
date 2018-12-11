#include "BBQ.h"
#include "Producer.h"
#include "Consumer.h"
#include "tsprintf.h"
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>

#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10

int main(int argc, char **argv)
{
    // Check if program was called with correct number of command-line arguemnts.
    if (argc != 3)
    {
        tsprintf("Error: project1 expected 2 arguments received %d\n", argc - 1);
        tsprintf("Usage: project1 [sleep time range limit in milliseconds for producing threads]\n");
        tsprintf("                [sleep time range limit in milliseconds for consuming threads]\n");
        exit(EXIT_FAILURE);
    }

    // Use current time as seed for random number generator.
    std::srand(std::time(nullptr));

    // Parse delay times from command line arguements.
    int max_producer_sleep_time_ms = std::atoi(*(argv + 1));
    int max_consumer_sleep_time_ms = std::atoi(*(argv + 2));


    std::srand(std::time(0));

    // Create shared blocking bounded queue.
    BBQ *bbq = new BBQ();

    // Initialize producer and consumer threads. These threads will run forever.
    std::vector<Producer*> producers;
    std::vector<Consumer*> consumers;
    std::vector<std::thread> producerThreads;
    std::vector<std::thread> consumerThreads;

    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        Producer *producer = new Producer(bbq, i + 1, max_producer_sleep_time_ms);
        producers.push_back(producer);
        bbq->registerObserver(producer);
    }

    for (int i = 0; i < NUM_PRODUCERS; ++i)
    { 
        // Create producer threads in separate loop so that all producers are 
        // registered as observers on the BBQ prior to creating threads.
        producerThreads.push_back(std::thread(&Producer::run, producers[i]));
        tsprintf("Created producer thread number %d\n", i + 1);
    }

    for (int i = NUM_PRODUCERS; i < NUM_PRODUCERS + NUM_CONSUMERS; ++i)
    {
        Consumer *consumer = new Consumer(bbq, i + 1, max_consumer_sleep_time_ms);
        consumers.push_back(consumer);
        consumerThreads.push_back(std::thread(&Consumer::run, consumer));
        tsprintf("Created consumer thread number %d\n", i + 1);
    }
        
    // Even though the threads will run forever, we need to call join on the 
    // threads so that the main thread will wait and not exit till the
    // producers and consumers are finished. In effect, this ensures the
    // program runs indefinitely, until the user interrupts the program using
    // CTRL + C or kills the program.
    for (auto &producerThread : producerThreads)
        producerThread.join();

    for (auto &consumerThread : consumerThreads)
        consumerThread.join();

    return 0;
}