#include "../incl/Person.hpp"
#include "../incl/Room.hpp"
#include "../incl/Course.hpp"
#include "../incl/Form.hpp"
#include <iostream>
#include <algorithm>

// Person implementation
Person::Person(std::string p_name) : _name(p_name), _currentRoom(NULL) {}
Person::~Person() {}

// Staff implementation
Staff::Staff(std::string p_name) : Person(p_name) {}
Staff::~Staff() {}

void Staff::sign(Form* p_form)
{
    if (p_form)
        p_form->sign();
}

// Student implementation
Student::Student(std::string p_name) : Person(p_name) {}
Student::~Student() {}

void Student::attendClass(Classroom* p_classroom)
{
    if (p_classroom && p_classroom->canEnter(this))
    {
        if (room())
            room()->exit(this);
        p_classroom->enter(this);
    }
}

void Student::exitClass()
{
    if (room())
        room()->exit(this);
}

void Student::graduate(Course* p_course)
{
    if (!p_course)
        return;
        
    std::vector<Course*>::iterator it = std::find(_subscribedCourse.begin(), 
                                                  _subscribedCourse.end(), 
                                                  p_course);
    if (it != _subscribedCourse.end())
    {
        _subscribedCourse.erase(it);
        p_course->removeStudent(this);
        std::cout << getName() << " graduated from " << p_course->getName() << std::endl;
    }
}

void Student::subscribeToCourse(Course* p_course)
{
    if (p_course && std::find(_subscribedCourse.begin(), 
                              _subscribedCourse.end(), 
                              p_course) == _subscribedCourse.end())
    {
        _subscribedCourse.push_back(p_course);
        p_course->subscribe(this);
    }
}

// Professor implementation
Professor::Professor(std::string p_name) : Staff(p_name), _currentCourse(NULL) {}
Professor::~Professor() {}

void Professor::assignCourse(Course* p_course)
{
    _currentCourse = p_course;
    if (p_course)
        p_course->assign(this);
}

void Professor::doClass()
{
    if (_currentCourse)
        std::cout << getName() << " is teaching " << _currentCourse->getName() << std::endl;
}

void Professor::closeCourse()
{
    _currentCourse = NULL;
}

// Secretary implementation
Secretary::Secretary(std::string p_name) : Staff(p_name) {}
Secretary::~Secretary() {}

Form* Secretary::createForm(int p_formType)
{
    switch(p_formType)
    {
        case CourseFinished:
            return new CourseFinishedForm();
        case NeedMoreClassRoom:
            return new NeedMoreClassRoomForm();
        case NeedCourseCreation:
            return new NeedCourseCreationForm();
        case SubscriptionToCourse:
            return new SubscriptionToCourseForm();
        default:
            return NULL;
    }
}

void Secretary::archiveForm(Form* p_form)
{
    // Archive form in secretarial office
    if (p_form)
        std::cout << "Form archived" << std::endl;
}

// Headmaster implementation
Headmaster::Headmaster(std::string p_name) : Staff(p_name) {}
Headmaster::~Headmaster() 
{
    for (size_t i = 0; i < _formToValidate.size(); ++i)
        delete _formToValidate[i];
}

void Headmaster::receiveForm(Form* p_form)
{
    if (p_form)
        _formToValidate.push_back(p_form);
}

void Headmaster::signForm(Form* p_form)
{
    if (p_form)
    {
        sign(p_form);
        std::cout << getName() << " signed a form" << std::endl;
    }
}

void Headmaster::executeForm(Form* p_form)
{
    if (p_form && p_form->isSigned())
    {
        p_form->execute();
        std::cout << getName() << " executed a form" << std::endl;
    }
}
