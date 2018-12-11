#ifndef BBQ_H
#define BBQ_H

#include "BBQObserver.h"
#include <mutex>
#include <condition_variable>
#include <vector>

#define BBQ_MAX_BUFFER_SIZE            10
#define BBQ_THREE_QUARTERS_BUFFER_SIZE ((BBQ_MAX_BUFFER_SIZE * 3) / 4)
#define BBQ_ONE_QUARTER_BUFFER_SIZE    (BBQ_MAX_BUFFER_SIZE / 4)

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
    inline bool canInsert(int thread_id);
    inline bool canRemove(int thread_id);
    
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
    void insert(int thread_id, int item);

    /**
     * 
     */
    void remove(int thread_id, int &item);

    /**
     * 
     */ 
    void registerObserver(BBQObserver *observer);

    /**
     * 
     */
    void notifyObservers(BBQObserverAction action);

};

#endif