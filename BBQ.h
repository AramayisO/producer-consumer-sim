#ifndef BBQ_H
#define BBQ_H

#include <mutex>
#include <condition_variable>

const int MAX = 10;

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

    // Helper functions
    inline bool hasSpace() { return (m_tail - m_head) < MAX; }
    inline bool hasItems() { return m_head < m_tail; }
    
public:
    BBQ();
    ~BBQ() {};
    void insert(int item);
    int remove();
};

#endif