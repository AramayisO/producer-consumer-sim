#ifndef CONSUMER_H
#define CONSUMER_H

#include "BBQ.h"

class Consumer
{
private:
    BBQ *bbq;
    int thread_id;
    int max_sleep_time;

public:
    Consumer(BBQ *_bbq, int id, int tc);

    void run();
};

#endif