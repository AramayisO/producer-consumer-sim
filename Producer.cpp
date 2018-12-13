#include "Producer.h"
#include "BBQObserver.h"
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

// This function will run indefinitely, attemting to insert
// a random value into the queue. It will cause the thread
// to block if the queue is full. After each insert, the 
// thread will sleep for some time in the range (0, max_sleep_time). 
// The sleep time is random and can change between consecutive
// remove operations.
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

// Callback allowing the BBQ to notify the producer of the action
// to take in response to a change of state in the BBQ. If the 
// BBQ is getting too full, the producer will decrease its rate
// of production by 10%. If the BBQ is getting too empty, the 
// producer will increase its rate of production by 10% up to
// twice the initial rate. Otherwise, the producer will reset 
// its rate of production to the initial rate.
void Producer::update(BBQObserverAction action)
{
    switch (action)
    {
        case BBQObserverAction::DecreaseProductionRate:
            max_sleep_time += static_cast<int>(initial_max_sleep_time * 0.1);
        break;

        case BBQObserverAction::IncreaseProductionRate:
            max_sleep_time -= static_cast<int>(initial_max_sleep_time * 0.1);
            if (max_sleep_time < (initial_max_sleep_time / 2))
            {
                max_sleep_time = initial_max_sleep_time / 2;
            }
        break;

        case BBQObserverAction::ResetProductionRate:
        default:
            max_sleep_time = initial_max_sleep_time;
        break;
    }
}

