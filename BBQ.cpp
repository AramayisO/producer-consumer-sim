#include "BBQ.h"
#include "BBQObserver.h"
#include <functional>

BBQ::BBQ() : head{0}, tail{0} {
    buffer = new int[MAX_BUFFER_SIZE];
}

BBQ::~BBQ() {
    delete buffer;
    buffer = nullptr;
}

int BBQ::insert(int thread_id, int item)
{
    // Acquire lock and check if there is space to add a new item.
    // Release lock and wait if there is no space. Otherwise,
    // insert item and return.
    std::unique_lock<std::mutex> lock(buffer_mutex);
    item_removed.wait(lock, std::bind(&BBQ::canInsert, this, thread_id));
    buffer[tail % MAX_BUFFER_SIZE] = item;
    tail++;
    
    // Notify observers if threshold exceeded or cleared.
    notifyObservers();
    
    // Signal that an item has been insert to allow a waiting
    // consumer thread to continue.
    item_added.notify_one();

    // Return ID of inserted item.
    return tail - 1;
}

int BBQ::remove(int thread_id, int &item)
{
    // Acquire lock and check if there is at least one item that can be removed.
    // Release lock and wait if there are no items in the buffer. Otherwise,
    // remove item and return.
    std::unique_lock<std::mutex> lock(buffer_mutex);
    item_added.wait(lock, std::bind(&BBQ::canRemove, this, thread_id));
    item = buffer[head % MAX_BUFFER_SIZE];
    head++;

    // Notify observers.
    notifyObservers();

    // Signal that an item has been removed to allow a waiting
    // producer thread to continue.
    item_removed.notify_one();
    
    // Return ID of removed item.
    return head - 1;
}

void BBQ::registerObserver(BBQObserver *observer)
{
    if (observer != nullptr)
    {
        observers.push_back(observer);
    }
}

void BBQ::notifyObservers()
{
    for (BBQObserver *observer : observers)
    {
        observer->update();
    }
}

bool BBQ::canInsert(int thread_id)
{
    if ((tail - head) < MAX_BUFFER_SIZE)
    {
        return true;
    }
    else
    {
        std::printf("Waiting to produce by thread number %d\n", thread_id);
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
        std::printf("Waiting to consume by thread number %d\n", thread_id);
        return false;
    }
}