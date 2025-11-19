#ifndef IEVENT_HPP
#define IEVENT_HPP

#include <string>

class Train;
class Rail;

/**
 * @interface IEvent
 * @brief Interface for simulation events
 * 
 * Part of Factory Pattern for creating different event types.
 */
class IEvent {
public:
    virtual ~IEvent() {}
    
    /**
     * @brief Execute the event effect
     */
    virtual void execute() = 0;
    
    /**
     * @brief Get event description
     */
    virtual std::string getDescription() const = 0;
};

#endif // IEVENT_HPP
