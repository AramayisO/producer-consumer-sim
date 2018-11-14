#include "TSQueue.h"
#include <functional>

// Default constructor to create a thread safe blocking bounded queue.
TSQueue::TSQueue(): head{0}, tail{0} {}

bool TSQueue::insert(int item, int &pos)
{
    bool inserted = false;

    std::lock_guard<std::mutex> lock(buffer_mutex);

    if (canInsert()) {
        pos = tail % MAX;
        buffer[pos] = item;
        tail++;
        inserted = true;
    }

    return inserted;
}

bool TSQueue::remove(int &item, int &pos) {

    bool removed = false;

    std::lock_guard<std::mutex> lock(buffer_mutex);

    if (canRemove()) {
        pos = head % MAX;
        item = buffer[pos];
        head++;
        removed = true;
    }

    return removed;
}