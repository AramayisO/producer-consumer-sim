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

public:
    /**
     * Create and initialize producer object.
     *
     * @param _bbq pointer to a shared bounded buffer queue.
     * @param id   id of the thread associated with producer object.
     * @param tp   initial sleep time range limit.
     */
    Producer(BBQ *_bbq, int id, int tp);

    /**
     * The function to be bound to a thread and intended to be executed
     * by the thread when it starts.
     */
    void run();

    /**
     * Callback allowing the BBQ to notify the producer of the action
     * to take in response to a change of state in the BBQ.
     * 
     * @param action the action the producer should take.
     */
    void update(BBQObserverAction action) override;
};

#endif
