#ifndef BBQ_H
#define BBQ_H

#include "BBQObserver.h"
#include <mutex>
#include <condition_variable>
#include <vector>

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
     * Allocate memory and initialize state.
     */
    BBQ();

    /**
     * Clean-up and release allocated memory.
     */ 
    ~BBQ();

    /**
     * Inserts an item at the back of the queue. If the queue is full,
     * the calling thread will block until notified that an item has
     * been removed from the queue.
     * 
     * @param thread_id id of the calling thread.
     * @param item      item to be added to the queue.
     */
    void insert(int thread_id, int item);

    /**
     * Removes an item from the front of the queue. If the queue is
     * empty, the calling thread will block until notified that an 
     * item has been added.
     * 
     * @param thread_id id of the calling thread.
     * @param item      output parameter which contains the value of 
     *                  the removed item if successful.
     */
    void remove(int thread_id, int &item);

    /**
     * Adds an observer to the queue's list of registered observers
     * that will be notified on particular threshold events by calling
     * the observers update function.
     */ 
    void registerObserver(BBQObserver *observer);

    /**
     * Notifies all registered observers that the BBQ size has reached
     * a threshold level and calls each observers update function with
     * the action that each observer should take.
     */
    void notifyObservers(BBQObserverAction action);
};

#endif
