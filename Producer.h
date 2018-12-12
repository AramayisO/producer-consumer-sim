#ifndef PRODUCER_H
#define PRODUCER_H

#include "BBQ.h"
#include "BBQObserver.h"

class Producer : public BBQObserver
{
private:
    BBQ *bbq;
    int thread_id;
    int initial_max_sleep_time;
    int max_sleep_time;

#ifdef FIXED_NUMBER_OF_ITERATIONS
    static int iteration;
#endif

public:
    Producer(BBQ *_bbq, int id, int tp);

    void run();

    void update(BBQObserverAction action) override;
};

#endif