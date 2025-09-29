#include "employeeManagement.hpp"
#include "hourlyEmployee.hpp"
#include "salariedEmployee.hpp"
#include <iostream>

int main() {
    EmployeeManager manager;
    
    // Create different types of employees
    TempWorker* temp1 = new TempWorker("John (Temp)", 15);
    TempWorker* temp2 = new TempWorker("Sarah (Temp)", 20);
    ContractEmployee* contract1 = new ContractEmployee("Michael (Contract)", 25, 154);
    Apprentice* apprentice1 = new Apprentice("Emma (Apprentice)", 12, 154);
    
    // Add employees to manager
    manager.addEmployee(temp1);
    manager.addEmployee(temp2);
    manager.addEmployee(contract1);
    manager.addEmployee(apprentice1);
    
    std::cout << "========================================" << std::endl;
    std::cout << "       EMPLOYEE MANAGEMENT DEMO" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    // === TEMP WORKERS ===
    std::cout << "--- Setting up Temp Workers ---" << std::endl;
    temp1->mobilize(100); // John will work 100 hours this month
    std::cout << "John mobilized for 100 hours" << std::endl;
    temp2->mobilize(80);  // Sarah will work 80 hours this month
    std::cout << "Sarah mobilized for 80 hours" << std::endl << std::endl;
    
    // === CONTRACT EMPLOYEE ===
    std::cout << "--- Setting up Contract Employee ---" << std::endl;
    std::cout << "Michael expected to work 154 hours this month" << std::endl;
    contract1->addNonWorkHours(14); // Michael took 2 days off (14 hours)
    std::cout << "Michael took 14 hours off (vacation/sick)" << std::endl << std::endl;
    
    // === APPRENTICE ===
    std::cout << "--- Setting up Apprentice ---" << std::endl;
    std::cout << "Emma expected to work 154 hours this month" << std::endl;
    apprentice1->addSchoolHours(35); // Emma goes to school 35 hours
    std::cout << "Emma has 35 hours of school (paid at half rate)" << std::endl;
    apprentice1->addNonWorkHours(7);  // Emma took 1 day off
    std::cout << "Emma took 7 hours off" << std::endl << std::endl;
    
    // Simulate a work week (5 days)
    std::cout << "========================================" << std::endl;
    std::cout << "       SIMULATING A WORK WEEK" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    for (int day = 1; day <= 5; day++) {
        std::cout << "--- Day " << day << " ---" << std::endl;
        manager.executeWorkday();
    }
    
    // More work days to simulate a month
    std::cout << "--- Simulating rest of the month (17 more days) ---" << std::endl;
    for (int day = 6; day <= 22; day++) {
        manager.executeWorkday();
    }
    
    // Calculate and display payroll
    std::cout << "========================================" << std::endl;
    std::cout << "         MONTHLY PAYROLL REPORT" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    std::cout << "Details:" << std::endl;
    std::cout << "  - John (Temp): 100 hours worked × $15/hr" << std::endl;
    std::cout << "  - Sarah (Temp): 80 hours worked × $20/hr" << std::endl;
    std::cout << "  - Michael (Contract): (154 - 14) hours × $25/hr" << std::endl;
    std::cout << "  - Emma (Apprentice): (154 - 35 - 7) hours × $12/hr" << std::endl;
    std::cout << "                       + 35 school hours × $6/hr" << std::endl << std::endl;

    manager.calculatePayroll();

    // Demonstrate Liskov Substitution Principle
    std::cout << "========================================" << std::endl;
    std::cout << "    LISKOV SUBSTITUTION PRINCIPLE" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    std::cout << "All employee types can be used interchangeably:" << std::endl;
    std::vector<Employee*> allEmployees;
    allEmployees.push_back(temp1);
    allEmployees.push_back(temp2);
    allEmployees.push_back(contract1);
    allEmployees.push_back(apprentice1);

    std::vector<Employee*>::iterator it;
    for (it = allEmployees.begin(); it != allEmployees.end(); ++it) {
        Employee* emp = *it;
        std::cout << "  - " << emp->getName() 
                  << " (Payroll: $" << emp->calculatePayroll() << ")" << std::endl;
    }
    std::cout << std::endl;
    
    // Demonstrate Interface Segregation Principle
    std::cout << "========================================" << std::endl;
    std::cout << "  INTERFACE SEGREGATION PRINCIPLE" << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    std::cout << "Each employee only implements interfaces it needs:" << std::endl;
    std::cout << "  - TempWorker: IWorkHourTracker, IMobilizable" << std::endl;
    std::cout << "  - ContractEmployee: INonWorkHourTracker" << std::endl;
    std::cout << "  - Apprentice: INonWorkHourTracker, ISchoolAttendee" << std::endl << std::endl;
    
    // Using specific interfaces
    IWorkHourTracker* tracker = temp1;
    std::cout << "Using IWorkHourTracker interface:" << std::endl;
    std::cout << "  John has worked " << tracker->getLoggedHours() << " hours" << std::endl << std::endl;

    ISchoolAttendee* student = apprentice1;
    std::cout << "Using ISchoolAttendee interface:" << std::endl;
    std::cout << "  Emma attended " << student->getSchoolHours() << " hours of school" << std::endl << std::endl;

    
    return 0;
}