#ifndef BBQ_H
#define BBQ_H

#include "BBQObserver.h"
#include <mutex>
#include <condition_variable>
#include <vector>

#define MAX_BUFFER_SIZE 10

class BBQ
{
private:
    // Synchronization variables.
    std::mutex buffer_mutex;
    std::condition_variable item_added;
    std::condition_variable item_removed;

    // State variables.
    int *buffer;
    int head;
    int tail;

    // Observer pattern used to notify all producers to modify their rate.
    std::vector<BBQObserver *> observers;

    // Helper functions.
    inline bool canInsert() { return (tail - head) < MAX_BUFFER_SIZE; }
    inline bool canRemove() { return head < tail; }

public:
    /**
     * 
     */
    BBQ();

    /**
     * 
     */ 
    ~BBQ();

    /**
     * 
     */
    int insert(int item);

    /**
     * 
     */
    int remove(int &item);

    /**
     * 
     */ 
    void registerObserver(BBQObserver *observer);

    /**
     * 
     */
    void notifyObservers();

};

#endif