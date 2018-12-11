#include "Producer.h"
#include "BBQObserver.h"
#include "tsprintf.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>

Producer::Producer(BBQ *_bbq, int id, int tp): 
    bbq{_bbq}, 
    thread_id{id}, 
    initial_max_sleep_time{tp},
    max_sleep_time{tp} 
    {}

void Producer::run()
{
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    while (true)
    {
        if (bbq != nullptr)
        {
            bbq->insert(thread_id, std::rand() % 100);
            sleep_for(milliseconds(std::rand() % max_sleep_time));
        }
    }
}

void Producer::update(BBQObserverAction action)
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