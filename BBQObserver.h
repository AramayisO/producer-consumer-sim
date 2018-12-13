#ifndef BBQ_OBSERVER_H
#define BBQ_OBSERVER_H

// Actions to be taken by the observer in
// response to state changes in the subject
// being observed.
enum class BBQObserverAction
{
    IncreaseProductionRate,
    DecreaseProductionRate,
    ResetProductionRate
};

class BBQObserver
{
public:
    virtual ~BBQObserver() {};

    /**
     * Callback to be called by the subject the observer is
     * registered to obser notifying the observer of the action
     * to take in response to a state change in the subject.
     */
    virtual void update(BBQObserverAction action) = 0;
};

#endif