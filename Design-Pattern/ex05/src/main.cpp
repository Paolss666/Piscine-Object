#include <iostream>
#include "../incl/School.hpp"

int main()
{
    std::cout << "=== EX05: Facade Pattern Test ===" << std::endl;
    std::cout << "School class provides a simple interface to complex operations\n" << std::endl;
    
    // FACADE PATTERN: Complex system hidden behind simple interface
    School* mySchool = new School();
    
    std::cout << "\n=== Recruiting Staff and Students ===" << std::endl;
    
    // Simple methods hide complex operations
    mySchool->recruteProfessor("Dr. Einstein");
    mySchool->recruteProfessor("Dr. Newton");
    mySchool->recruteProfessor("Dr. Curie");
    
    mySchool->recruteStudent("Alice");
    mySchool->recruteStudent("Bob");
    mySchool->recruteStudent("Charlie");
    mySchool->recruteStudent("Diana");
    mySchool->recruteStudent("Eve");
    mySchool->recruteStudent("Frank");
    
    std::cout << "\n=== Getting School Information ===" << std::endl;
    
    // Easy access to information
    std::vector<Student*> students = mySchool->getStudents();
    std::vector<Professor*> professors = mySchool->getProfessors();
    
    std::cout << "School has " << students.size() << " students" << std::endl;
    std::cout << "School has " << professors.size() << " professors" << std::endl;
    
    // Check specific course
    Course* einstein_course = mySchool->getCourse("Dr. Einstein's Course");
    if (einstein_course)
    {
        std::cout << "Found course: " << einstein_course->getName() << std::endl;
    }
    
    std::cout << "\n=== Running Complete Day Routine ===" << std::endl;
    std::cout << "One method call orchestrates entire complex day!" << std::endl;
    
    // FACADE IN ACTION: One simple call manages everything
    mySchool->runDayRoutine();
    
    std::cout << "\n=== Testing Individual Facade Methods ===" << std::endl;
    
    // Can also call individual simplified methods
    std::cout << "\n--- Launch Classes ---" << std::endl;
    mySchool->launchClasses();
    
    std::cout << "\n--- Ring Bell ---" << std::endl;
    mySchool->requestRingBell();
    
    std::cout << "\n--- Ring Bell Again ---" << std::endl;
    mySchool->requestRingBell();
    
    std::cout << "\n=== Graduation Ceremony ===" << std::endl;
    mySchool->graduationCeremony();
    
    std::cout << "\n=== Running Multiple Days ===" << std::endl;
    for (int day = 1; day <= 3; ++day)
    {
        std::cout << "\n>>> DAY " << day << " <<<" << std::endl;
        mySchool->runDayRoutine();
    }
    
    std::cout << "\n=== Final Graduation Ceremony ===" << std::endl;
    mySchool->graduationCeremony();
    
    std::cout << "\n=== Facade Pattern Summary ===" << std::endl;
    std::cout << "✓ School class provides simple interface to complex system" << std::endl;
    std::cout << "✓ runDayRoutine() orchestrates multiple patterns and objects" << std::endl;
    std::cout << "✓ Client doesn't need to know about Forms, Bells, Observers, etc." << std::endl;
    std::cout << "✓ Complex interactions hidden behind simple method calls" << std::endl;
    std::cout << "✓ Combines Singleton, Factory, Command, Mediator, and Observer patterns" << std::endl;
    std::cout << "✓ All complexity is encapsulated in the School facade!" << std::endl;
    
    delete mySchool;
    
    return 0;
}
