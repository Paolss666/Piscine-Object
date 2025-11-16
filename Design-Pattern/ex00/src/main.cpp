#include <iostream>
#include "../incl/Person.hpp"
#include "../incl/Room.hpp"
#include "../incl/Course.hpp"
#include "../incl/Form.hpp"
#include "../incl/Event.hpp"

int main()
{
    std::cout << "=== EX00: File Decomposition Test ===" << std::endl;
    std::cout << "\nSuccessfully decomposed the datas.hpp file into:" << std::endl;
    std::cout << "- Person.hpp/cpp (Person, Staff, Student, Professor, Secretary, Headmaster)" << std::endl;
    std::cout << "- Room.hpp/cpp (Room, Classroom, SecretarialOffice, etc.)" << std::endl;
    std::cout << "- Course.hpp/cpp (Course class)" << std::endl;
    std::cout << "- Form.hpp/cpp (Form and derived classes)" << std::endl;
    std::cout << "- Event.hpp (Event enum)" << std::endl;
    
    std::cout << "\n=== Testing basic functionality ===" << std::endl;
    
    // Create some people
    Student* student1 = new Student("Alice");
    Professor* prof1 = new Professor("Dr. Smith");
    Secretary* secretary = new Secretary("Ms. Johnson");
    Headmaster* headmaster = new Headmaster("Mr. Brown");
    
    // Create a course
    Course* math = new Course("Mathematics");
    prof1->assignCourse(math);
    
    // Create rooms
    Classroom* classroom1 = new Classroom();
    Courtyard* courtyard = new Courtyard();
    
    // Test room entry
    std::cout << "\nTesting room functionality:" << std::endl;
    courtyard->enter(student1);
    courtyard->enter(prof1);
    courtyard->printOccupant();
    
    // Test course subscription
    std::cout << "\nTesting course subscription:" << std::endl;
    student1->subscribeToCourse(math);
    
    // Clean up
    delete student1;
    delete prof1;
    delete secretary;
    delete headmaster;
    delete math;
    delete classroom1;
    delete courtyard;
    
    std::cout << "\n=== All files compiled and linked successfully! ===" << std::endl;
    
    return 0;
}
