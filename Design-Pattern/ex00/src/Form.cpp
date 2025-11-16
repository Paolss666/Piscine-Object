#include "../incl/Form.hpp"
#include "../incl/Person.hpp"
#include "../incl/Course.hpp"
#include "../incl/Room.hpp"
#include <iostream>

// Form implementation
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
    if (isSigned() && _student && _course)
    {
        _student->graduate(_course);
        std::cout << "CourseFinishedForm executed for " 
                  << _student->getName() << std::endl;
    }
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
    if (isSigned() && _newRoom)
    {
        // Room is created by setting _newRoom
        std::cout << "NeedMoreClassRoomForm executed: new classroom created" << std::endl;
    }
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
    if (isSigned() && !_courseName.empty())
    {
        if (!_newCourse)
            _newCourse = new Course(_courseName);
        std::cout << "NeedCourseCreationForm executed: course " 
                  << _courseName << " created" << std::endl;
    }
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
    if (isSigned() && _student && _course)
    {
        _student->subscribeToCourse(_course);
        std::cout << "SubscriptionToCourseForm executed for " 
                  << _student->getName() << std::endl;
    }
}
