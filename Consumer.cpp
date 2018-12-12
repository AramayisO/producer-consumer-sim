#include "Consumer.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include <cstdlib>

#ifdef FIXED_NUMBER_OF_ITERATIONS
    extern int MAX_NUMBER_OF_ITERATIONS;
#endif

Consumer::Consumer(BBQ *_bbq, int id, int tc): 
    bbq{_bbq}, 
    thread_id{id}, 
    max_sleep_time{tc} 
    {}

void Consumer::run()
{
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    while (true
#ifdef FIXED_NUMBER_OF_ITERATIONS
        && Consumer::iteration < MAX_NUMBER_OF_ITERATIONS
#endif
    )
    {
#ifdef FIXED_NUMBER_OF_ITERATIONS
        Consumer::iteration++;
#endif
        if (bbq != nullptr)
        {
            int item;
            bbq->remove(thread_id, item);
            sleep_for(milliseconds(std::rand() % max_sleep_time));
        }
    }
}

#ifdef FIXED_NUMBER_OF_ITERATIONS
    int Consumer::iteration = 0;
#endif