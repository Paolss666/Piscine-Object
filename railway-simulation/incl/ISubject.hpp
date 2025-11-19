#ifndef ISUBJECT_HPP
#define ISUBJECT_HPP

#include "IObserver.hpp"
#include <vector>

/**
 * @interface ISubject
 * @brief Observer Pattern - Subject interface
 * 
 * Manages observers and notifies them of events.
 */
class ISubject {
protected:
    std::vector<IObserver*> _observers;
    
public:
    virtual ~ISubject() {}
    
    virtual void attach(IObserver* observer) {
        _observers.push_back(observer);
    }
    
    virtual void detach(IObserver* observer) {
        for (size_t i = 0; i < _observers.size(); ++i) {
            if (_observers[i] == observer) {
                _observers.erase(_observers.begin() + i);
                break;
            }
        }
    }
    
    virtual void notify(const std::string& event) {
        for (size_t i = 0; i < _observers.size(); ++i) {
            _observers[i]->onNotify(event);
        }
    }
};

#endif // ISUBJECT_HPP
