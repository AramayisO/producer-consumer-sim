#ifndef BBQ_H
#define BBQ_H

#include <mutex>
#include <condition_variable>

static const int MAX = 10;

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
    BBQ();
    ~BBQ() {};
    int insert(int item);
    int remove(int &item);
};

#endif