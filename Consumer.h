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
    /**
     * Create and initialize consumer object.
     *
     * @param _bbq pointer to a shared bounded buffer queue.
     * @param id   id of the thread associated with producer object.
     * @param tc   initial sleep time range limit.
     */
    Consumer(BBQ *_bbq, int id, int tc);

    /**
     * The function to be bound to a thread and intended to be executed
     * by the thread when it starts.
     */
    void run();
};

#endif
