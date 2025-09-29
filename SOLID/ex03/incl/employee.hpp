#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <stdexcept>

class Employee
{
private:
    std::string _name;
    int _hourlyValue;
public:
    Employee(const std::string &name, int hourlyValue) : _name(name), _hourlyValue(hourlyValue) {
        if (name.empty()) {
            throw std::invalid_argument("Employee name cannot be empty.");
        }
        if (hourlyValue < 0) {
            throw std::invalid_argument("Employee hourly value cannot be negative.");
        }
    }

    virtual ~Employee() {}

    std::string getName() const {
        return _name;
    }

    int getHourlyValue() const {
        return _hourlyValue;
    }

    virtual int calculatePayroll() = 0;
    virtual void executeWorkday() = 0;

};


// iterface for employees who track work hours
// class IHourlyWork {

class IWorkHourTracker {
public:
    virtual ~IWorkHourTracker() {}
    virtual void logWorkHours(int hours) = 0;
    virtual int getLoggedHours() const = 0;
};

// interface for employees who track non-worked hours (e.g., sick leave, vacation)
class INonWorkHourTracker {
public:
    virtual ~INonWorkHourTracker() {}
    virtual void logNonWorkHours(int hours) = 0;
    virtual int getNonWorkHours() const = 0;
};

class ISchoolAttendee {
public:
    virtual ~ISchoolAttendee() {}
    virtual void attendSchool(int hours) = 0;
    virtual int getSchoolHours() const = 0;
};

class IMobilizable{
public:
    virtual ~IMobilizable() {}
    virtual void mobilize(int hours) = 0;
    // virtual int getMobilizedHours() const = 0;
};

#endif