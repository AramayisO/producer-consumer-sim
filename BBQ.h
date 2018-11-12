#ifndef BBQ_H
#define BBQ_H

#include <mutex>
#include <condition_variable>

static const int MAX = 20;

class BBQ
{
private:
    // Synchronization variables
    std::mutex m_mutex;
    std::condition_variable m_itemAdded;
    std::condition_variable m_itemRemoved;

    // State variables
    int m_items[MAX];
    int m_head;
    int m_tail;

    // // Helper functions
    inline bool canInsert() { return (m_tail - m_head) < MAX; }
    inline bool canRemove() { return m_head < m_tail; }
    
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
     * @param item - Output parameter to which removed item is copied.
     * @return Returns position of removed item.
     */
    int remove(int &item);
};

#endif