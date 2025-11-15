#include "Form.hpp"
#include "Person.hpp"
#include "Course.hpp"
#include "Room.hpp"
#include "singletons.hpp"
#include <iostream>

// Form implementation - Command Pattern base
Form::Form(FormType p_formType) : _formType(p_formType), _isSigned(false) {}
Form::~Form() {}

// CourseFinishedForm implementation
CourseFinishedForm::CourseFinishedForm() : 
    Form(CourseFinished), 
    _student(NULL), 
    _course(NULL) 
{
}

CourseFinishedForm::~CourseFinishedForm() {}

void CourseFinishedForm::execute()
{
    if (!isSigned())
    {
        std::cout << "CourseFinishedForm cannot be executed: not signed!" << std::endl;
        return;
    }
    
    if (!_student || !_course)
    {
        std::cout << "CourseFinishedForm cannot be executed: missing information!" << std::endl;
        return;
    }
    
    _student->graduate(_course);
    std::cout << "CourseFinishedForm executed: " 
              << _student->getName() << " graduated from "
              << _course->getName() << std::endl;
}

// NeedMoreClassRoomForm implementation
NeedMoreClassRoomForm::NeedMoreClassRoomForm() : 
    Form(NeedMoreClassRoom), 
    _newRoom(NULL) 
{
}

NeedMoreClassRoomForm::~NeedMoreClassRoomForm() {}

void NeedMoreClassRoomForm::execute()
{
    if (!isSigned())
    {
        std::cout << "NeedMoreClassRoomForm cannot be executed: not signed!" << std::endl;
        return;
    }
    
    // Create a new classroom and add it to the RoomList
    Classroom* newClassroom = new Classroom();
    RoomList::getInstance().add(newClassroom);
    _newRoom = newClassroom;
    
    std::cout << "NeedMoreClassRoomForm executed: new classroom created with ID " 
              << newClassroom->getID() << std::endl;
}

// NeedCourseCreationForm implementation
NeedCourseCreationForm::NeedCourseCreationForm() : 
    Form(NeedCourseCreation), 
    _newCourse(NULL) 
{
}

NeedCourseCreationForm::~NeedCourseCreationForm() {}

void NeedCourseCreationForm::execute()
{
    if (!isSigned())
    {
        std::cout << "NeedCourseCreationForm cannot be executed: not signed!" << std::endl;
        return;
    }
    
    if (_courseName.empty())
    {
        std::cout << "NeedCourseCreationForm cannot be executed: no course name!" << std::endl;
        return;
    }
    
    // Create new course and add to CourseList
    _newCourse = new Course(_courseName);
    CourseList::getInstance().add(_newCourse);
    
    std::cout << "NeedCourseCreationForm executed: course '" 
              << _courseName << "' created" << std::endl;
}

// SubscriptionToCourseForm implementation
SubscriptionToCourseForm::SubscriptionToCourseForm() : 
    Form(SubscriptionToCourse), 
    _student(NULL), 
    _course(NULL) 
{
}

SubscriptionToCourseForm::~SubscriptionToCourseForm() {}

void SubscriptionToCourseForm::execute()
{
    if (!isSigned())
    {
        std::cout << "SubscriptionToCourseForm cannot be executed: not signed!" << std::endl;
        return;
    }
    
    if (!_student || !_course)
    {
        std::cout << "SubscriptionToCourseForm cannot be executed: missing information!" << std::endl;
        return;
    }
    
    if (_course->isFull())
    {
        std::cout << "SubscriptionToCourseForm cannot be executed: course is full!" << std::endl;
        return;
    }
    
    _student->subscribeToCourse(_course);
    std::cout << "SubscriptionToCourseForm executed: " 
              << _student->getName() << " subscribed to "
              << _course->getName() << std::endl;
}
