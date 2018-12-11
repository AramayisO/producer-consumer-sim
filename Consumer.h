#ifndef CONSUMER_H
#define CONSUMER_H

#include "BBQ.h"
#include "tsprintf.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>

class Consumer
{
private:
    BBQ *bbq;
    int thread_id;
    int max_sleep_time;

public:
    Consumer(BBQ *_bbq, int id, int tc): bbq{_bbq}, thread_id{id}, max_sleep_time{tc} {}

    void run()
    {
        while (true)
        {
            if (bbq != nullptr)
            {
                int item;
                int item_id = bbq->remove(thread_id, item);
                tsprintf("Item ID %d consumed by thread number %d\n", item_id, thread_id);
                std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % max_sleep_time));
            }
        }
    }
};

#endif