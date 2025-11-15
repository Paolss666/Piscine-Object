#include <iostream>
#include "incl/Person.hpp"
#include "incl/Room.hpp"
#include "incl/Course.hpp"
#include "incl/Form.hpp"
#include "incl/singletons.hpp"
#include "incl/observer.hpp"

int main()
{
    std::cout << "=== EX04: Observer Pattern Test ===" << std::endl;
    std::cout << "The Bell notifies all students and professors when it rings\n" << std::endl;
    
    // Create the headmaster who will ring the bell
    Headmaster* headmaster = new Headmaster("Mr. Director");
    Secretary* secretary = new Secretary("Ms. Secretary");
    headmaster->setSecretary(secretary);
    
    std::cout << "=== Setting up the school ===" << std::endl;
    
    // Create professors (they automatically register to the bell)
    Professor* mathProf = new Professor("Dr. Einstein");
    Professor* physicsProf = new Professor("Dr. Newton");
    
    // Create students (they automatically register to the bell)
    Student* alice = new Student("Alice");
    Student* bob = new Student("Bob");
    Student* charlie = new Student("Charlie");
    Student* diana = new Student("Diana");
    
    // Create courses
    headmaster->requestCourseCreation(mathProf, "Mathematics");
    headmaster->requestCourseCreation(physicsProf, "Physics");
    
    Course* mathCourse = CourseList::getInstance().getByName("Mathematics");
    Course* physicsCourse = CourseList::getInstance().getByName("Physics");
    
    // Subscribe students to courses
    if (mathCourse)
    {
        headmaster->requestCourseSubscription(alice, mathCourse);
        headmaster->requestCourseSubscription(bob, mathCourse);
    }
    
    if (physicsCourse)
    {
        headmaster->requestCourseSubscription(charlie, physicsCourse);
        headmaster->requestCourseSubscription(diana, physicsCourse);
    }
    
    std::cout << "\n=== Classes are starting ===" << std::endl;
    
    // Professors start teaching
    mathProf->doClass();
    physicsProf->doClass();
    
    // Students attend classes
    Classroom* class1 = new Classroom();
    Classroom* class2 = new Classroom();
    RoomList::getInstance().add(class1);
    RoomList::getInstance().add(class2);
    
    class1->assignCourse(mathCourse);
    class2->assignCourse(physicsCourse);
    
    alice->attendClass(class1);
    bob->attendClass(class1);
    charlie->attendClass(class2);
    diana->attendClass(class2);
    
    std::cout << "\n=== First Bell Ring (Start Break) ===" << std::endl;
    // OBSERVER PATTERN IN ACTION: Ring the bell for break
    headmaster->bellRing();
    
    std::cout << "\n--- Status during break ---" << std::endl;
    std::cout << "Alice in class: " << (alice->isInClass() ? "YES" : "NO") << std::endl;
    std::cout << "Bob in class: " << (bob->isInClass() ? "YES" : "NO") << std::endl;
    std::cout << "Math Prof teaching: " << (mathProf->isTeaching() ? "YES" : "NO") << std::endl;
    std::cout << "Physics Prof teaching: " << (physicsProf->isTeaching() ? "YES" : "NO") << std::endl;
    
    std::cout << "\n=== Second Bell Ring (End Break) ===" << std::endl;
    // Ring the bell to end break
    headmaster->bellRing();
    
    std::cout << "\n--- Status after break ends ---" << std::endl;
    std::cout << "Alice in class: " << (alice->isInClass() ? "YES" : "NO") << std::endl;
    std::cout << "Bob in class: " << (bob->isInClass() ? "YES" : "NO") << std::endl;
    std::cout << "Math Prof teaching: " << (mathProf->isTeaching() ? "YES" : "NO") << std::endl;
    std::cout << "Physics Prof teaching: " << (physicsProf->isTeaching() ? "YES" : "NO") << std::endl;
    
    std::cout << "\n=== Third Bell Ring (Lunch Break) ===" << std::endl;
    headmaster->bellRing();
    
    std::cout << "\n=== Fourth Bell Ring (Back from Lunch) ===" << std::endl;
    headmaster->bellRing();
    
    std::cout << "\n=== Observer Pattern Summary ===" << std::endl;
    std::cout << "✓ Bell is a Subject that notifies all Observers" << std::endl;
    std::cout << "✓ Students and Professors are Observers of the Bell" << std::endl;
    std::cout << "✓ When bell rings, all observers react automatically" << std::endl;
    std::cout << "✓ Students leave/enter classes based on bell" << std::endl;
    std::cout << "✓ Professors stop/resume teaching based on bell" << std::endl;
    std::cout << "✓ No polling needed - push notification system!" << std::endl;
    
    // Cleanup
    delete headmaster;
    delete secretary;
    delete mathProf;
    delete physicsProf;
    delete alice;
    delete bob;
    delete charlie;
    delete diana;
    
    return 0;
}
