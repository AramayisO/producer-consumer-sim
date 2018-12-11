#include "BBQ.h"
#include "BBQObserver.h"
#include "tsprintf.h"
#include <functional>

BBQ::BBQ() : head{0}, tail{0} {
    buffer = new int[BBQ_MAX_BUFFER_SIZE];
}

BBQ::~BBQ() {
    delete buffer;
    buffer = nullptr;
}

void BBQ::insert(int thread_id, int item)
{
    // Acquire lock and check if there is space to add a new item.
    // Release lock and wait if there is no space. Otherwise,
    // insert item and return.
    std::unique_lock<std::mutex> lock(buffer_mutex);
    item_removed.wait(lock, std::bind(&BBQ::canInsert, this, thread_id));
    buffer[tail % BBQ_MAX_BUFFER_SIZE] = item;
    tail++;

    tsprintf("Item ID %d produced by thread number %d\n", tail - 1, thread_id);

    // Notify observers if threshold exceeded or cleared.
    if ((tail - head) >= BBQ_THREE_QUARTERS_BUFFER_SIZE)
    {
        notifyObservers(BBQObserverAction::DecreaseProductionRate);
    }
    else if ((tail - head) <= BBQ_ONE_QUARTER_BUFFER_SIZE)
    {
        notifyObservers(BBQObserverAction::IncreaseProductionRate);
    }
    else
    {
        notifyObservers(BBQObserverAction::ResetProductionRate);
    }
    
    // Signal that an item has been insert to allow a waiting
    // consumer thread to continue.
    item_added.notify_one();
}

void BBQ::remove(int thread_id, int &item)
{
    // Acquire lock and check if there is at least one item that can be removed.
    // Release lock and wait if there are no items in the buffer. Otherwise,
    // remove item and return.
    std::unique_lock<std::mutex> lock(buffer_mutex);
    item_added.wait(lock, std::bind(&BBQ::canRemove, this, thread_id));
    item = buffer[head % BBQ_MAX_BUFFER_SIZE];
    head++;

    tsprintf("Item ID %d consumed by thread number %d\n", head - 1, thread_id);

    // Notify observers if threshold exceeded or cleared.
    if ((tail - head) >= BBQ_THREE_QUARTERS_BUFFER_SIZE)
    {
        notifyObservers(BBQObserverAction::DecreaseProductionRate);
    }
    else if ((tail - head) <= BBQ_ONE_QUARTER_BUFFER_SIZE)
    {
        notifyObservers(BBQObserverAction::IncreaseProductionRate);
    }
    else
    {
        notifyObservers(BBQObserverAction::ResetProductionRate);
    }

    // Signal that an item has been removed to allow a waiting
    // producer thread to continue.
    item_removed.notify_one();
}

void BBQ::registerObserver(BBQObserver *observer)
{
    if (observer != nullptr)
    {
        observers.push_back(observer);
    }
}

void BBQ::notifyObservers(BBQObserverAction action)
{
    for (BBQObserver *observer : observers)
    {
        observer->update(action);
    }
}

bool BBQ::canInsert(int thread_id)
{
    if ((tail - head) < BBQ_MAX_BUFFER_SIZE)
    {
        return true;
    }
    else
    {
        tsprintf("Waiting to produce by thread number %d\n", thread_id);
        return false;
    }
}

bool BBQ::canRemove(int thread_id)
{
    if (head < tail)
    {
        return true;
    }
    else
    {
        tsprintf("Waiting to consume by thread number %d\n", thread_id);
        return false;
    }
}