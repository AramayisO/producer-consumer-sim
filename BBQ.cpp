#include "BBQ.h"
#include <functional>

// Default constructor to create a thread safe blocking bounded queue.
BBQ::BBQ(): head{0}, tail{0} {}

std::size_t BBQ::insert(int item)
{
    // Acquire lock and check if there is space to add a new item.
    // Release lock and wait if there is no space.
    std::unique_lock<std::mutex> lock(buffer_mutex);
    item_removed.wait(lock, std::bind(&BBQ::canInsert, this));

    // Add item to buffer and return the position where item was added.
    buffer[tail % MAX] = item;
    tail++;

    // Signal that an item has been to allow a waiting consumer thread
    // to continue.
    item_added.notify_one();

    return tail - 1;
}

std::size_t BBQ::remove(int &item)
{
    // Acquire lock and check if there is at least one item that can be removed.
    // Release lock and wait if there is are no items in the buffersa.
    std::unique_lock<std::mutex> lock(buffer_mutex);
    item_added.wait(lock, std::bind(&BBQ::canRemove, this));

    // Remove item from buffer. Write value of removed item to output parameter
    // and return position where item was removed.
    item = buffer[head % MAX];
    head++;

    // Signal that an item has been removed to allow a waiting producer thread
    // to continue.
    item_removed.notify_one();

    return head - 1;
}