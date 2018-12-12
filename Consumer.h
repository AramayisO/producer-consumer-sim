#ifndef CONSUMER_H
#define CONSUMER_H

#include "BBQ.h"

class Consumer
{
private:
    BBQ *bbq;
    int thread_id;
    int max_sleep_time;

#ifdef FIXED_NUMBER_OF_ITERATIONS
    static int iteration;
#endif

public:
    Consumer(BBQ *_bbq, int id, int tc);

    void run();
};

#endif