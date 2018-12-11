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
    int initial_max_sleep_time;
    int max_sleep_time;

public:
    Producer(BBQ *_bbq, int id, int tp): 
        bbq{_bbq}, 
        thread_id{id}, 
        initial_max_sleep_time{tp},
        max_sleep_time{tp} 
        {}

    void run()
    {
        while (true)
        {
            if (bbq != nullptr)
            {
                bbq->insert(thread_id, std::rand() % BBQ_MAX_BUFFER_SIZE);
                std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % max_sleep_time));
            }
        }
    }

    void update(BBQObserverAction action) override
    {
        switch (action)
        {
            case BBQObserverAction::DecreaseProductionRate:
                max_sleep_time += max_sleep_time * 0.1;
            break;

            case BBQObserverAction::IncreaseProductionRate:
                max_sleep_time -= max_sleep_time * 0.1;
            break;

            case BBQObserverAction::ResetProductionRate:
            default:
                max_sleep_time = initial_max_sleep_time;
            break;
        }
    }
};

#endif