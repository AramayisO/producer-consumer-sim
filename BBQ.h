#ifndef BBQ_H
#define BBQ_H

#include <mutex>
#include <condition_variable>

constexpr int MAX = 20;

class BBQ
{
private:
    // Synchronization variables
    std::mutex buffer_mutex;
    std::condition_variable item_added;
    std::condition_variable item_removed;

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
    BBQ();

    /**
     * Default destructor.
     */
    ~BBQ() {};

    /**
     * Inserts a new item into the buffer if buffer is not full. Otherwise,
     * waits until space becomes available.
     * 
     * @param item - Item to be inserted.
     * @return Returns the position at which the item was inserted.
     */
    int insert(int item);

    /**
     * Removes an item from the buffer if buffer is not empty. Otherwise,
     * waits until there is an available item in the buffer.
     * 
     * @param item - Output parameter in which removed item is copied.
     * @return Returns position of removed item.
     */
    int remove(int &item);
};

#endif