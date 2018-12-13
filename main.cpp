#include "BBQ.h"
#include "Producer.h"
#include "Consumer.h"
#include "ThreadSafeIO.h"
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>

#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10


// ============================================================================
// = main: Entry point into the program. Creates NUM_PRODUCER producer threads 
// =       and NUM_CONSUMER consumer threads that share a single BBQ object. 
// =       Each thread runs indefinitely with a random sleep time between 
// =       consecutive insert and remove operations within the range 
// =       (0, max_producer_sleep_time_ms) and  (0, max_consumer_sleep_time_ms) 
// =       where max_producer_sleep_time_ms and max_consumer_sleep_time_ms are 
// =       in milliseconds and passed in as command-line arguments.
// ============================================================================
int main(int argc, char **argv)
{
    // Check if program was called with correct number of command-line arguemnts.
    if (argc != 3)
    {
        ThreadSafeIO::printf("Error: project1 expected 2 arguments received %d\n", argc - 1);
        ThreadSafeIO::printf("Usage: project1 [sleep time range limit in milliseconds for producing threads]\n");
        ThreadSafeIO::printf("                [sleep time range limit in milliseconds for consuming threads]\n");
        exit(EXIT_FAILURE);
    }

    // This will ensure that the random sleep times for producer and
    // consumer threads are different each time the program is run.
    std::srand(std::time(nullptr));

    // Parse initial sleep times from command line arguements.
    int max_producer_sleep_time_ms = std::atoi(*(argv + 1));
    int max_consumer_sleep_time_ms = std::atoi(*(argv + 2));

    // Create shared blocking bounded queue. We allocate the queue on the
    // heap rather than on the stack since it is best practice to allocate
    // objects that will be shared by multiple threads on the heap.
    BBQ *bbq = new BBQ();

    // Just some state to keep track of allocated resources.
    std::vector<Producer*> producers;
    std::vector<Consumer*> consumers;
    std::vector<std::thread> producerThreads;
    std::vector<std::thread> consumerThreads;

    // Create producer objects and register them as observers on the BBQ object.
    // This will allow the BBQ to notify the producers when certain events occur,
    // such as the BBQ becoming some percentage full or empty, and the producers
    // can adjust their rate of production in response.
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    {
        Producer *producer = new Producer(bbq, i + 1, max_producer_sleep_time_ms);
        producers.push_back(producer);
        bbq->registerObserver(producer);
    }

    // Create producer threads in separate loop so that all producers are 
    // registered as observers on the BBQ prior to creating threads.
    for (int i = 0; i < NUM_PRODUCERS; ++i)
    { 
        producerThreads.push_back(std::thread(&Producer::run, producers[i]));
        ThreadSafeIO::printf("Created producer thread number %d\n", i + 1);
    }

    // Create consumer objects and threads.
    for (int i = NUM_PRODUCERS; i < NUM_PRODUCERS + NUM_CONSUMERS; ++i)
    {
        Consumer *consumer = new Consumer(bbq, i + 1, max_consumer_sleep_time_ms);
        consumers.push_back(consumer);
        consumerThreads.push_back(std::thread(&Consumer::run, consumer));
        ThreadSafeIO::printf("Created consumer thread number %d\n", i + 1);
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

    
    // Cleanup, even though it's not necessary since the producer and consumer
    // threads will run forever until the program is terminated by the user,
    // just as good habit.
    for (Producer *producer : producers)
    {
        if (producer != nullptr)
            delete producer;
    }

    for (Consumer *consumer : consumers)
    {
        if (consumer != nullptr)
            delete consumer;
    }

    return EXIT_SUCCESS;
}
