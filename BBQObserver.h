#ifndef BBQ_OBSERVER_H
#define BBQ_OBSERVER_H

enum class BBQObserverAction
{
    IncreaseProductionRate,
    DecreaseProductionRate,
    ResetProductionRate
};

class BBQObserver
{
public:
    virtual void update(BBQObserverAction action) = 0;
};

#endif