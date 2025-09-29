#ifndef EMPLOYEEMAnager_HPP
#define EMPLOYEEMAnager_HPP

#include "employee.hpp"
#include "salariedEmployee.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

class EmployeeManager {
private:
    std::vector<Employee*> employees;

public:
    void addEmployee(Employee* emp){
        if (!emp){
            throw std::invalid_argument("Cannot add null employee.");
        }
        std::vector<Employee*>::iterator it = std::find(employees.begin(), employees.end(), emp);
        if (it != employees.end()){
            throw std::invalid_argument("Employee already exists.");
        }
        employees.push_back(emp);
    }

    void removeEmployee(Employee* emp){
        std::vector<Employee*>::iterator it = std::find(employees.begin(), employees.end(), emp);
        if (it == employees.end()){
            throw std::invalid_argument("Employee not found.");
        }
        employees.erase(it);
    }

    void executeWorkday() {
        std::cout << "=== Executing Workday (7 hours) ===" << std::endl;

        for (std::vector<Employee*>::iterator it = employees.begin(); it != employees.end(); ++it) {
            Employee* emp = *it;
            emp->executeWorkday();
            std::cout << "  " << emp->getName() << " worked today" << std::endl;
        }
        std::cout << std::endl;
    }

    void calculatePayroll(){
        std::cout << "=== Monthly Payroll Calculation ===" << std::endl;
        int total = 0;
        std::vector<Employee*>::iterator it;
        for (it = employees.begin(); it != employees.end(); ++it){
            Employee* emp = *it;
            int payroll = emp->calculatePayroll();
            total += payroll;
            std::cout << "  " << emp->getName() << ": " << payroll << " euros" << std::endl;
        }
        std::cout << "Total Payroll: " << total << " euros" << std::endl << std::endl;
    }

    size_t getEmployeeCount() const {
        return employees.size();
    }

    ~EmployeeManager() {
        for (std::vector<Employee*>::iterator it = employees.begin(); it != employees.end(); ++it) {
            Employee* emp = *it;
            delete emp;
        }
        // employees.erase(employees.begin(), employees.end());
        employees.clear();
    }
};

#endif 