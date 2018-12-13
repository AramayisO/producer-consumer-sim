#include "Consumer.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>

Consumer::Consumer(BBQ *_bbq, int id, int tc): 
    bbq{_bbq}, 
    thread_id{id}, 
    max_sleep_time{tc} 
    {}

// This function will run indefinitely, attemting to remove
// an item from the queue. It will cause the thread to block 
// if the queue is empty. After each remove, the thread will
// sleep for some time in the range (0, max_sleep_time). The
// sleep time is random and can change between consecutive
// remove operations.
void Consumer::run()
{
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    while (true)
    {
        if (bbq != nullptr)
        {
            int item;
            bbq->remove(thread_id, item);
            sleep_for(milliseconds(std::rand() % max_sleep_time));
        }
    }
}
