#ifndef EVENTFACTORY_HPP
#define EVENTFACTORY_HPP

#include "IEvent.hpp"
#include "Train.hpp"
#include "Rail.hpp"
#include <cstdlib>

/**
 * @class DelayEvent
 * @brief Event that causes train delay
 */
class DelayEvent : public IEvent {
private:
    Train* _train;
    int _delayMinutes;
    
public:
    DelayEvent(Train* train, int delayMinutes) 
        : _train(train), _delayMinutes(delayMinutes) {}
    
    virtual void execute();
    virtual std::string getDescription() const;
};

/**
 * @class SpeedReductionEvent
 * @brief Event that reduces speed limit on a rail
 */
class SpeedReductionEvent : public IEvent {
private:
    Rail* _rail;
    double _reductionPercent;
    
public:
    SpeedReductionEvent(Rail* rail, double reductionPercent)
        : _rail(rail), _reductionPercent(reductionPercent) {}
    
    virtual void execute();
    virtual std::string getDescription() const;
};

/**
 * @class EventFactory
 * @brief Factory Pattern - Creates random events
 * 
 * Implements Factory Pattern to create different types of events.
 * SOLID Principle: Single Responsibility - only creates events
 */
class EventFactory {
public:
    static IEvent* createRandomEvent(Train* train);
    static IEvent* createRandomEvent(Rail* rail);
    
private:
    EventFactory(); // Private constructor - utility class
};

#endif // EVENTFACTORY_HPP
