#ifndef PRODUCER_H
#define PRODUCER_H

#include "BBQ.h"
#include "BBQObserver.h"
#include "tsprintf.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>

class Producer : public BBQObserver
{
private:
    BBQ *bbq;
    int thread_id;
    int max_sleep_time;

public:
    Producer(BBQ *_bbq, int id, int tp): bbq{_bbq}, thread_id{id}, max_sleep_time{tp} {}

    void run()
    {
        while (true)
        {
            if (bbq != nullptr)
            {
                int item_id = bbq->insert(thread_id, thread_id);
                tsprintf("Item ID %d produced by thread number %d\n", item_id, thread_id);
                std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % max_sleep_time));
            }
        }
    }

    void update() override
    {
        // std::printf("Updated thread %d\n", thread_id);
    }
};

#endif