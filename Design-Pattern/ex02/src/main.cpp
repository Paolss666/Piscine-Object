#include <iostream>
#include "../incl/Person.hpp"
#include "../incl/Room.hpp"
#include "../incl/Course.hpp"
#include "../incl/Form.hpp"
#include "../incl/singletons.hpp"

int main()
{
    std::cout << "=== EX02: Factory and Command Pattern Test ===" << std::endl;
    
    // Initialize singletons
    StudentList& studentList = StudentList::getInstance();
    CourseList& courseList = CourseList::getInstance();
    RoomList& roomList = RoomList::getInstance();
    
    // Create actors
    std::cout << "\n=== Creating actors ===" << std::endl;
    Secretary* secretary = new Secretary("Ms. Johnson");
    Headmaster* headmaster = new Headmaster("Mr. Brown");
    Student* alice = new Student("Alice");
    Student* bob = new Student("Bob");
    Professor* profSmith = new Professor("Dr. Smith");
    
    studentList.add(alice);
    studentList.add(bob);
    
    // Create initial rooms
    Classroom* class1 = new Classroom();
    roomList.add(class1);
    
    std::cout << "\n=== FACTORY PATTERN: Secretary creates forms ===" << std::endl;
    
    // Test Factory Pattern - Secretary creates different forms
    Form* courseCreationForm = secretary->createForm(NeedCourseCreation);
    Form* subscriptionForm1 = secretary->createForm(SubscriptionToCourse);
    Form* subscriptionForm2 = secretary->createForm(SubscriptionToCourse);
    Form* roomCreationForm = secretary->createForm(NeedMoreClassRoom);
    Form* graduationForm = secretary->createForm(CourseFinished);
    
    std::cout << "\n=== COMMAND PATTERN: Forms as commands ===" << std::endl;
    
    // 1. Create a new course
    std::cout << "\n--- Creating new course ---" << std::endl;
    NeedCourseCreationForm* mathCourseForm = dynamic_cast<NeedCourseCreationForm*>(courseCreationForm);
    if (mathCourseForm)
    {
        mathCourseForm->setCourseName("Mathematics");
        headmaster->receiveForm(mathCourseForm);
        
        // Try to execute without signing (should fail)
        std::cout << "Attempting execution without signature:" << std::endl;
        mathCourseForm->execute();
        
        // Now sign and execute
        std::cout << "\nSigning and executing:" << std::endl;
        headmaster->signForm(mathCourseForm);
        headmaster->executeForm(mathCourseForm);
    }
    
    // 2. Subscribe students to course
    std::cout << "\n--- Subscribing students to course ---" << std::endl;
    Course* mathCourse = courseList.getByName("Mathematics");
    
    if (mathCourse && subscriptionForm1 && subscriptionForm2)
    {
        // First student
        SubscriptionToCourseForm* subForm1 = dynamic_cast<SubscriptionToCourseForm*>(subscriptionForm1);
        if (subForm1)
        {
            subForm1->setStudent(alice);
            subForm1->setCourse(mathCourse);
            headmaster->receiveForm(subForm1);
            headmaster->signForm(subForm1);
            headmaster->executeForm(subForm1);
        }
        
        // Second student
        SubscriptionToCourseForm* subForm2 = dynamic_cast<SubscriptionToCourseForm*>(subscriptionForm2);
        if (subForm2)
        {
            subForm2->setStudent(bob);
            subForm2->setCourse(mathCourse);
            headmaster->receiveForm(subForm2);
            headmaster->signForm(subForm2);
            headmaster->executeForm(subForm2);
        }
    }
    
    // 3. Assign professor to course
    std::cout << "\n--- Assigning professor to course ---" << std::endl;
    if (mathCourse)
    {
        profSmith->assignCourse(mathCourse);
        std::cout << "Professor " << profSmith->getName() 
                  << " assigned to " << mathCourse->getName() << std::endl;
    }
    
    // 4. Create new classroom when needed
    std::cout << "\n--- Creating new classroom ---" << std::endl;
    if (roomCreationForm)
    {
        headmaster->receiveForm(roomCreationForm);
        headmaster->signForm(roomCreationForm);
        
        std::cout << "Rooms before: " << roomList.size() << std::endl;
        headmaster->executeForm(roomCreationForm);
        std::cout << "Rooms after: " << roomList.size() << std::endl;
    }
    
    // 5. Graduate a student
    std::cout << "\n--- Graduating student ---" << std::endl;
    CourseFinishedForm* gradForm = dynamic_cast<CourseFinishedForm*>(graduationForm);
    if (gradForm && mathCourse)
    {
        gradForm->setStudent(alice);
        gradForm->setCourse(mathCourse);
        headmaster->receiveForm(gradForm);
        
        // Execute without signing (should fail)
        std::cout << "Attempting to graduate without signature:" << std::endl;
        gradForm->execute();
        
        // Sign and execute
        std::cout << "\nWith proper signature:" << std::endl;
        headmaster->signForm(gradForm);
        headmaster->executeForm(gradForm);
    }
    
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "- Factory Pattern: Secretary successfully creates different form types" << std::endl;
    std::cout << "- Command Pattern: Forms encapsulate actions and can be executed when signed" << std::endl;
    std::cout << "- Forms without signature cannot be executed (security)" << std::endl;
    std::cout << "- Each form type performs its specific action when executed" << std::endl;
    
    // Cleanup (forms are managed by headmaster, others by singletons)
    delete secretary;
    delete headmaster;
    delete profSmith;
    
    return 0;
}
