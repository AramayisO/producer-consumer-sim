#include <thread>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "BBQ.h"

constexpr int NUM_PRODUCERS{10};
constexpr int NUM_CONSUMERS{10};

void producerTask(const BBQ &arg, int max_sleep_time_ms)
{
    BBQ &bbq = const_cast<BBQ&>(arg);
    int sleep_time_ms = std::rand() % max_sleep_time_ms;
    while (true)
    {
        int item_id = bbq.insert(std::rand());
        std::printf("Item ID %d produced by thread number 0x%x\n", item_id, std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_ms));
    }
}

void consumerTask(const BBQ &arg, int max_sleep_time_ms)
{
    BBQ &bbq = const_cast<BBQ&>(arg);
    int sleep_time_ms = std::rand() % max_sleep_time_ms;
    while (true)
    {
        int item;
        int item_id = bbq.remove(item);
        std::printf("Item ID %d consumed by thread number 0x%x\n", item_id, std::this_thread::get_id());
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time_ms));
    }
}

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
        std::printf("Created producer thread %d\n", i);

    }

    // Create consuming threads.
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.push_back(std::thread(consumerTask, std::ref(bbq), consumers_max_sleep_time_ms));
        std::printf("Created consumer thread %d\n", i);
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