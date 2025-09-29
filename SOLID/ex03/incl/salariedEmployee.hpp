#ifndef SALARIEDEMPLOYEE_HPP
#define SALARIEDEMPLOYEE_HPP

#include "employee.hpp"

// ContractEmployee: has expected monthly hours, tracks non-worked hours
class ContractEmployee : public Employee, public INonWorkHourTracker {
private:
    int expectedMonthlyHours; // Standard: 7 hours/day * 22 working days = 154 hours
    int nonWorkedHours;

public:
    ContractEmployee(const std::string& name, int hourlyValue, int expectedHours = 154) 
        : Employee(name, hourlyValue), 
          expectedMonthlyHours(expectedHours), 
          nonWorkedHours(0) {}

    virtual ~ContractEmployee() {}

    virtual void logNonWorkHours(int hours) {
        if (hours < 0) {
            throw std::invalid_argument("Non-worked hours cannot be negative.");
        }
        nonWorkedHours += hours;
    }

    virtual int getNonWorkHours() const {
        return nonWorkedHours;
    }
    
    virtual void addNonWorkHours(int hours) {
        nonWorkedHours += hours;
    }
    
    virtual int getNonWorkedHours() const {
        return nonWorkedHours;
    }
    
    virtual void executeWorkday() {
        // Contract employee works by default, nothing to track unless absent
        // Absence must be registered separately via addNonWorkHours
    }

    virtual int calculatePayroll() {
        int actualWorkedHours = expectedMonthlyHours - nonWorkedHours;
        return actualWorkedHours * getHourlyValue();
    }
    
    // Reset for new month
    void resetMonthlyHours() {
        nonWorkedHours = 0;
    }
};

// Apprentice: like ContractEmployee but also attends school (paid at half rate)
class Apprentice : public Employee, public INonWorkHourTracker, public ISchoolAttendee {
private:
    int expectedMonthlyHours;
    int nonWorkedHours;
    int schoolHours;

public:
    Apprentice(const std::string& name, int hourlyValue, int expectedHours = 154) 
        : Employee(name, hourlyValue), 
          expectedMonthlyHours(expectedHours), 
          nonWorkedHours(0), 
          schoolHours(0) {}

    virtual void addNonWorkHours(int hours) {
        nonWorkedHours += hours;
    }

    virtual void logNonWorkHours(int hours) {
        if (hours < 0) {
            throw std::invalid_argument("Non-worked hours cannot be negative.");
        }
        nonWorkedHours = hours;
    }

    virtual void  attendSchool(int hours) {
        if (hours < 0) {
            throw std::invalid_argument("School hours cannot be negative.");
        }
        schoolHours += hours;
    }

    virtual int getNonWorkHours() const {
        return nonWorkedHours;
    }

    virtual void addSchoolHours(int hours)  {
        schoolHours += hours;
    }

    virtual int getSchoolHours() const {
        return schoolHours;
    }
    
    virtual void executeWorkday() {
        // Apprentice works by default, absences and school time tracked separately
    }

    virtual int calculatePayroll() {
        int actualWorkedHours = expectedMonthlyHours - nonWorkedHours - schoolHours;
        int workPay = actualWorkedHours * getHourlyValue();
        int schoolPay = schoolHours * (getHourlyValue() / 2);
        return workPay + schoolPay;
    }
    
    // Reset for new month
    void resetMonthlyHours() {
        nonWorkedHours = 0;
        schoolHours = 0;
    }
};

#endif