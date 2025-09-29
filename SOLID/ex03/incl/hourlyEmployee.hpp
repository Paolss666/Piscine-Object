#ifndef HOURLYEMPLOYEE_HPP
#define HOURLYEMPLOYEE_HPP

#include "employee.hpp"
#include <stdexcept>

class TempWorker : public Employee, public IWorkHourTracker, public IMobilizable
{
private:
    int _workedHours;
    int _mobilizedHours;
public:
    TempWorker(const std::string &name, int hourlyValue): Employee(name, hourlyValue), _workedHours(0), _mobilizedHours(0) {};
    ~TempWorker(){};

    void addWorkedHours(int hours){
        if (hours < 0) {
            throw std::invalid_argument("Worked hours cannot be negative.");
        }
        _workedHours += hours;
    }

    int getWorkedHours() const {
        return _workedHours;
    }

    virtual void logWorkHours(int hours) {
        if (hours < 0) {
            throw std::invalid_argument("Logged hours cannot be negative.");
        }
        _workedHours += hours;
    }
    virtual int getMobilizedHours() const {
        return _mobilizedHours;
    }

    virtual int getLoggedHours() const {
        return _workedHours;
    }

    virtual void mobilize(int hours) {
        if (hours < 0) {
            throw std::invalid_argument("Mobilized hours cannot be negative.");
        }
        _mobilizedHours = hours;
    }

    virtual void executeWorkday()  {
        if (_mobilizedHours > 0) {
            int hoursToWork = (_mobilizedHours >= 7) ? 7 : _mobilizedHours;
            addWorkedHours(hoursToWork);
            _mobilizedHours -= hoursToWork;
            }
    }

    virtual int calculatePayroll() {
        return getWorkedHours() * getHourlyValue();
    }

    void resetWorkedHours() {
        _workedHours = 0;
    }

};

#endif
