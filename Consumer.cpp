#include "Consumer.h"
#include "tsprintf.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>

Consumer::Consumer(BBQ *_bbq, int id, int tc): 
    bbq{_bbq}, 
    thread_id{id}, 
    max_sleep_time{tc} 
    {}

void Consumer::run()
{
    while (true)
    {
        if (bbq != nullptr)
        {
            int item;
            bbq->remove(thread_id, item);
            std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % max_sleep_time));
        }
    }
}