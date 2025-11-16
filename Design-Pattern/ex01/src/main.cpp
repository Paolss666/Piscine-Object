#include <iostream>
#include "../incl/Person.hpp"
#include "../incl/Room.hpp"
#include "../incl/Course.hpp"
#include "../incl/Form.hpp"
#include "../incl/singletons.hpp"

int main()
{
    std::cout << "=== EX01: Singleton Pattern Test ===" << std::endl;
    
    // Get singleton instances
    StudentList& studentList = StudentList::getInstance();
    StaffList& staffList = StaffList::getInstance();
    CourseList& courseList = CourseList::getInstance();
    RoomList& roomList = RoomList::getInstance();
    
    std::cout << "\n=== Creating and adding students ===" << std::endl;
    Student* alice = new Student("Alice");
    Student* bob = new Student("Bob");
    Student* charlie = new Student("Charlie");
    
    studentList.add(alice);
    studentList.add(bob);
    studentList.add(charlie);
    
    std::cout << "Total students: " << studentList.size() << std::endl;
    
    std::cout << "\n=== Creating and adding staff ===" << std::endl;
    Professor* profSmith = new Professor("Dr. Smith");
    Professor* profJones = new Professor("Dr. Jones");
    Secretary* secretary = new Secretary("Ms. Johnson");
    Headmaster* headmaster = new Headmaster("Mr. Brown");
    
    staffList.add(profSmith);
    staffList.add(profJones);
    staffList.add(secretary);
    staffList.add(headmaster);
    
    std::cout << "Total staff: " << staffList.size() << std::endl;
    
    std::cout << "\n=== Creating and adding courses ===" << std::endl;
    Course* math = new Course("Mathematics");
    Course* physics = new Course("Physics");
    Course* chemistry = new Course("Chemistry");
    
    courseList.add(math);
    courseList.add(physics);
    courseList.add(chemistry);
    
    std::cout << "Total courses: " << courseList.size() << std::endl;
    
    std::cout << "\n=== Creating and adding rooms ===" << std::endl;
    Classroom* class1 = new Classroom();
    Classroom* class2 = new Classroom();
    Courtyard* courtyard = new Courtyard();
    StaffRestRoom* staffRoom = new StaffRestRoom();
    SecretarialOffice* secOffice = new SecretarialOffice();
    HeadmasterOffice* headOffice = new HeadmasterOffice();
    
    roomList.add(class1);
    roomList.add(class2);
    roomList.add(courtyard);
    roomList.add(staffRoom);
    roomList.add(secOffice);
    roomList.add(headOffice);
    
    std::cout << "Total rooms: " << roomList.size() << std::endl;
    
    std::cout << "\n=== Testing singleton access from different points ===" << std::endl;
    
    // Access the same lists from "another part of the program"
    StudentList& studentList2 = StudentList::getInstance();
    std::cout << "Accessing StudentList again - same instance: " 
              << (&studentList == &studentList2 ? "YES" : "NO") << std::endl;
    
    // Test retrieval by name
    std::cout << "\n=== Testing retrieval ===" << std::endl;
    Student* foundStudent = studentList.getByName("Bob");
    if (foundStudent)
        std::cout << "Found student: " << foundStudent->getName() << std::endl;
    
    Course* foundCourse = courseList.getByName("Physics");
    if (foundCourse)
        std::cout << "Found course: " << foundCourse->getName() << std::endl;
    
    // Test getting available classroom
    Classroom* availableClass = roomList.getAvailableClassroom();
    if (availableClass)
        std::cout << "Found available classroom with ID: " << availableClass->getID() << std::endl;
    
    std::cout << "\n=== Listing all students ===" << std::endl;
    const std::vector<Student*>& allStudents = studentList.getAll();
    for (size_t i = 0; i < allStudents.size(); ++i)
    {
        std::cout << "  - " << allStudents[i]->getName() << std::endl;
    }
    
    std::cout << "\n=== Singleton Pattern successfully implemented! ===" << std::endl;
    std::cout << "Note: Singletons automatically clean up on program exit" << std::endl;
    
    return 0;
}
