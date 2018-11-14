#include <thread>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "BBQ.h"

constexpr int NUM_PRODUCERS{10};
constexpr int NUM_CONSUMERS{10};

/**
 * Infinitely looping task that inserts a random value at each iteration into a
 * shared bounded buffer queue. The thread will sleep for some random time in the
 * range (0, max_sleep_time_ms) milliseconds between consecutive insert operations.
 * 
 * @param _bbq Bounded buffer queue in which values will be inserted.
 * 
 * @param max_sleep_time_ms Upper bound for the amound of time the thread will
 *                          between consecutive insert operations in milliseconds.
 */
void producerTask(const BBQ &_bbq, int max_sleep_time_ms)
{
    BBQ &bbq = const_cast<BBQ&>(_bbq);
    
    while (true)
    {
        int item_id = bbq.insert(std::rand());
        std::printf("Item ID %2d produced by thread number 0x%x\n", item_id, std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % max_sleep_time_ms));
    }
}

/**
 * Infinitely looping task that removes a value at each iteration from a shared
 * bounded buffer queue. The thread will sleep for some random time in the range
 * (0, max_sleep_time_ms) milliseconds between consecutive remove operations
 * 
 * @param _bbq Bounded buffer queue from which values will be removed.
 * 
 * @param max_sleep_time_ms Upper bound for the amound of time the thread will
 *                          between consecutive remove operations in milliseconds.
 */
void consumerTask(const BBQ &arg, int max_sleep_time_ms)
{
    BBQ &bbq = const_cast<BBQ&>(arg);
    
    while (true)
    {
        int item;
        int item_id = bbq.remove(item);
        std::printf("Item ID %2d consumed by thread number 0x%x\n", item_id, std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % max_sleep_time_ms));
    }
}

// ============================================================================
// = Main: Entry point into the program.
// =       Creates NUM_PRODUCER producing threads and NUM_CONSUMER consuming
// =       that share an instance of a BBQ. Each thread runs indefinitely with 
// =       a random sleep time between consecutive insert and remove operations
// =       within the range (0, producers_max_sleep_time_ms) and 
// =       (0, consumer_max_sleep_time_ms) where producers_max_sleep_time_ms 
// =       and consumer_max_sleep_time_ms are in milliseconds and passed in as
// =       command-line arguments.
// ============================================================================
int main(int argc, char **argv)
{
    // Check if program was called with correct number of command-line arguemnts.
    if (argc != 3)
    {
        std::printf("Error: project1 expected 2 arguments received %d\n", argc - 1);
        std::printf("Usage: project1 [sleep time range limit in milliseconds for producing threads]\n");
        std::printf("                [sleep time range limit in milliseconds for consuming threads]\n");
        exit(EXIT_FAILURE);
    }

    // Use current time as seed for random number generator.
    std::srand(std::time(nullptr));

    // Parse delay times from command line arguements.
    int producers_max_sleep_time_ms = std::atoi(*(argv + 1));
    int consumers_max_sleep_time_ms = std::atoi(*(argv + 2));

    // Create shared blocking bounded queue.
    BBQ bbq;

    // Initialize producer and consumer threads. These threads will run forever.
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // Create producing threads.
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.push_back(std::thread(producerTask, std::ref(bbq), producers_max_sleep_time_ms));
        // std::printf("Created producer thread %d\n", i);

    }

    // Create consuming threads.
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.push_back(std::thread(consumerTask, std::ref(bbq), consumers_max_sleep_time_ms));
        // std::printf("Created consumer thread %d\n", i);
    }

    // Even though the threads will run forever, we need to call join on the 
    // threads so that the main thread will wait and not exit till the
    // producers and consumers are finished. In effect, this ensures the
    // program runs indefinitely, until the user interrupts the program using
    // CTRL + C or kills the program.
    for (auto &producer : producers) {
        if (producer.joinable()) {
            producer.join();
        }
    }

    for (auto &consumer : consumers) {
        if (consumer.joinable()) {
            consumer.join();
        }
    }

    return EXIT_SUCCESS;
}