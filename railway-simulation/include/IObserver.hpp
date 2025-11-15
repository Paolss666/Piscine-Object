#ifndef IOBSERVER_HPP
#define IOBSERVER_HPP

#include <string>

/**
 * @interface IObserver
 * @brief Observer Pattern - Interface for observers
 * 
 * Allows objects to be notified of events in the simulation.
 * SOLID Principle: Dependency Inversion - depend on abstractions
 */
class IObserver {
public:
    virtual ~IObserver() {}
    
    /**
     * @brief Called when an event occurs
     * @param event Description of the event
     */
    virtual void onNotify(const std::string& event) = 0;
};

#endif // IOBSERVER_HPP
