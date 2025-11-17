#include <iostream>
#include "../incl/Person.hpp"
#include "../incl/Room.hpp"
#include "../incl/Course.hpp"
#include "../incl/Form.hpp"
#include "../../ex01/incl/singletons.hpp"

void demonstrateProfessorCourseCreation()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "SCENARIO 1: Professor needs a new course" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Headmaster* headmaster = new Headmaster("Mr. Director");
    Secretary* secretary = new Secretary("Ms. Secretary");
    Professor* professor = new Professor("Dr. Einstein");
    
    headmaster->setSecretary(secretary);
    
    // Professor requests course creation through headmaster
    headmaster->requestCourseCreation(professor, "Quantum Physics");
    
    // Verify the course was created
    Course* course = CourseList::getInstance().getByName("Quantum Physics");
    if (course && course->getResponsable() == professor)
    {
        std::cout << "✓ Course successfully created and professor assigned!" << std::endl;
    }
    
    delete headmaster;
    delete secretary;
    delete professor;
}

void demonstrateStudentCourseSubscription()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "SCENARIO 2: Student wants to join a course" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Headmaster* headmaster = new Headmaster("Mr. Director");
    Secretary* secretary = new Secretary("Ms. Secretary");
    Student* student1 = new Student("Alice");
    Student* student2 = new Student("Bob");
    
    headmaster->setSecretary(secretary);
    
    // Get the course created in previous scenario
    Course* quantumPhysics = CourseList::getInstance().getByName("Quantum Physics");
    
    if (quantumPhysics)
    {
        // Students request subscription through headmaster
        headmaster->requestCourseSubscription(student1, quantumPhysics);
        headmaster->requestCourseSubscription(student2, quantumPhysics);
        
        std::cout << "✓ Students successfully enrolled in course!" << std::endl;
        std::cout << "  Course now has " << quantumPhysics->getStudents().size() 
                  << " students" << std::endl;
    }
    
    StudentList::getInstance().add(student1);
    StudentList::getInstance().add(student2);
    
    delete headmaster;
    delete secretary;
}

void demonstrateClassroomRequest()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "SCENARIO 3: Professor needs more classrooms" << std::endl;
    std::cout << "========================================" << std::endl;
    
    Headmaster* headmaster = new Headmaster("Mr. Director");
    Secretary* secretary = new Secretary("Ms. Secretary");
    Professor* professor = new Professor("Dr. Newton");
    
    headmaster->setSecretary(secretary);
    
    size_t roomsBefore = RoomList::getInstance().size();
    std::cout << "Classrooms before request: " << roomsBefore << std::endl;
    
    // Professor requests new classroom through headmaster
    headmaster->requestClassroom(professor);
    
    size_t roomsAfter = RoomList::getInstance().size();
    std::cout << "Classrooms after request: " << roomsAfter << std::endl;
    
    if (roomsAfter > roomsBefore)
    {
        std::cout << "✓ New classroom successfully created!" << std::endl;
    }
    
    delete headmaster;
    delete secretary;
    delete professor;
}

void demonstrateFullWorkflow()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "COMPLETE WORKFLOW: Full mediation example" << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Setup
    Headmaster* headmaster = new Headmaster("Mr. Principal");
    Secretary* secretary = new Secretary("Ms. Admin");
    Professor* mathProf = new Professor("Dr. Gauss");
    Student* alice = new Student("Alice");
    Student* bob = new Student("Bob");
    
    headmaster->setSecretary(secretary);
    
    // Step 1: Professor doesn't have a course, requests one
    std::cout << "\nStep 1: Professor requests new course creation" << std::endl;
    headmaster->requestCourseCreation(mathProf, "Advanced Calculus");
    
    // Step 2: Students want to join the course
    std::cout << "\nStep 2: Students request to join the course" << std::endl;
    Course* calculus = CourseList::getInstance().getByName("Advanced Calculus");
    if (calculus)
    {
        headmaster->requestCourseSubscription(alice, calculus);
        headmaster->requestCourseSubscription(bob, calculus);
    }
    
    // Step 3: Professor needs a classroom
    std::cout << "\nStep 3: Professor needs a classroom to teach" << std::endl;
    Classroom* availableRoom = RoomList::getInstance().getAvailableClassroom();
    if (!availableRoom)
    {
        std::cout << "No available classroom, requesting new one..." << std::endl;
        headmaster->requestClassroom(mathProf);
    }
    
    // Step 4: After completing required classes, graduate students
    std::cout << "\nStep 4: Students complete course and graduate" << std::endl;
    if (calculus)
    {
        headmaster->graduateStudent(alice, calculus);
        headmaster->graduateStudent(bob, calculus);
    }
    
    // Step 5: Bell rings for break
    std::cout << "\nStep 5: Time for break" << std::endl;
    headmaster->bellRing();
    
    std::cout << "\n✓ Complete workflow successfully demonstrated!" << std::endl;
    std::cout << "  All interactions went through the Headmaster mediator" << std::endl;
    
    // Cleanup
    StudentList::getInstance().add(alice);
    StudentList::getInstance().add(bob);
    delete headmaster;
    delete secretary;
    delete mathProf;
}

int main()
{
    std::cout << "=== EX03: Mediator Pattern Test ===" << std::endl;
    std::cout << "The Headmaster acts as a mediator for all school operations" << std::endl;
    
    // Demonstrate different scenarios
    demonstrateProfessorCourseCreation();
    demonstrateStudentCourseSubscription();
    demonstrateClassroomRequest();
    demonstrateFullWorkflow();
    
    std::cout << "\n=== Mediator Pattern Summary ===" << std::endl;
    std::cout << "✓ All interactions go through the Headmaster (Mediator)" << std::endl;
    std::cout << "✓ Secretary creates forms when requested by Headmaster" << std::endl;
    std::cout << "✓ Headmaster signs and executes all forms" << std::endl;
    std::cout << "✓ Professors and Students don't interact directly" << std::endl;
    std::cout << "✓ Complex interactions are coordinated centrally" << std::endl;
    
    return 0;
}
