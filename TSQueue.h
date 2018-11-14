#ifndef TSQueue_H
#define TSQueue_H

#include <mutex>

constexpr int MAX = 20;

class TSQueue
{
private:
    // Synchronization variables
    std::mutex buffer_mutex;

    // State variables
    int buffer[MAX];
    int head;
    int tail;

    // Helper functions
    inline bool canInsert() { return (tail - head) < MAX; }
    inline bool canRemove() { return head < tail; }
    
public:
    /**
     * Default constructor
     */
    TSQueue();

    /**
     * Default destructor.
     */
    ~TSQueue() {};

    /**
     * Inserts a new item at the end of the buffer if it is not full.
     * 
     * @param item the item to be inserted.
     * @param pos  if successful, position of the inserted item.
     * @return     true if insert succeeded, false otherwise.
     */
    bool insert(int item, int &pos);

    /**
     * Removes an item from the front of the buffer if it is not empty.
     * 
     * @param item if successful, value of the item removed.
     * @param pos  if successful, position of the removed item.
     * @return     true if remove succeeded, false otherwise.
     */
    bool remove(int &item, int &pos);
};

#endif