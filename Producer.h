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
    Producer(BBQ *_bbq, int id, int tp);

    void run();

    void update(BBQObserverAction action) override;
};

#endif