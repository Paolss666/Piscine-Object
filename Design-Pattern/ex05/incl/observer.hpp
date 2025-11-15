#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <algorithm>
#include "Event.hpp"

// Observer interface
class IObserver
{
public:
    virtual ~IObserver() {}
    virtual void update(Event event) = 0;
};

// Subject (Observable) class
class Bell
{
private:
    std::vector<IObserver*> _observers;
    bool _isBreakTime;
    
    // Singleton pattern for the bell
    Bell() : _isBreakTime(false) {}
    Bell(const Bell&);
    Bell& operator=(const Bell&);
    
public:
    static Bell& getInstance()
    {
        static Bell instance;
        return instance;
    }
    
    void attach(IObserver* observer)
    {
        if (observer && std::find(_observers.begin(), _observers.end(), observer) == _observers.end())
        {
            _observers.push_back(observer);
        }
    }
    
    void detach(IObserver* observer)
    {
        std::vector<IObserver*>::iterator it = std::find(_observers.begin(), _observers.end(), observer);
        if (it != _observers.end())
        {
            _observers.erase(it);
        }
    }
    
    void ring()
    {
        _isBreakTime = !_isBreakTime;
        notify(RingBell);
    }
    
    bool isBreakTime() const { return _isBreakTime; }
    
private:
    void notify(Event event)
    {
        for (std::vector<IObserver*>::iterator it = _observers.begin(); 
             it != _observers.end(); ++it)
        {
            (*it)->update(event);
        }
    }
};

#endif // OBSERVER_HPP
