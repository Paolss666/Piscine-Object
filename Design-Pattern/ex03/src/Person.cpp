#include "Person.hpp"
#include "Room.hpp"
#include "Course.hpp"
#include "Form.hpp"
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
    Form* form = NULL;
    
    // Factory Pattern implementation
    switch(p_formType)
    {
        case CourseFinished:
            form = new CourseFinishedForm();
            std::cout << getName() << " created a CourseFinishedForm" << std::endl;
            break;
        case NeedMoreClassRoom:
            form = new NeedMoreClassRoomForm();
            std::cout << getName() << " created a NeedMoreClassRoomForm" << std::endl;
            break;
        case NeedCourseCreation:
            form = new NeedCourseCreationForm();
            std::cout << getName() << " created a NeedCourseCreationForm" << std::endl;
            break;
        case SubscriptionToCourse:
            form = new SubscriptionToCourseForm();
            std::cout << getName() << " created a SubscriptionToCourseForm" << std::endl;
            break;
        default:
            std::cout << getName() << " cannot create unknown form type" << std::endl;
            return NULL;
    }
    
    return form;
}

void Secretary::archiveForm(Form* p_form)
{
    // Archive form in secretarial office
    if (p_form)
        std::cout << "Form archived" << std::endl;
}

// Headmaster implementation - MEDIATOR PATTERN
Headmaster::Headmaster(std::string p_name) : Staff(p_name), _secretary(NULL) {}
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

// Mediator Pattern Implementation
void Headmaster::requestCourseCreation(Professor* professor, const std::string& courseName)
{
    if (!professor || !_secretary)
    {
        std::cout << "Cannot process course creation request" << std::endl;
        return;
    }
    
    std::cout << "\n[MEDIATOR] " << professor->getName() 
              << " requests course creation for: " << courseName << std::endl;
    
    // Secretary creates the form
    Form* form = _secretary->createForm(NeedCourseCreation);
    NeedCourseCreationForm* courseForm = dynamic_cast<NeedCourseCreationForm*>(form);
    
    if (courseForm)
    {
        // Fill the form
        courseForm->setCourseName(courseName);
        
        // Sign and execute
        signForm(courseForm);
        executeForm(courseForm);
        
        // Assign professor to the new course
        Course* newCourse = courseForm->getNewCourse();
        if (newCourse)
        {
            professor->assignCourse(newCourse);
            std::cout << "[MEDIATOR] " << professor->getName() 
                      << " assigned to new course: " << courseName << std::endl;
        }
    }
    delete form;
}

void Headmaster::requestCourseSubscription(Student* student, Course* course)
{
    if (!student || !course || !_secretary)
    {
        std::cout << "Cannot process subscription request" << std::endl;
        return;
    }
    
    std::cout << "\n[MEDIATOR] " << student->getName() 
              << " requests subscription to: " << course->getName() << std::endl;
    
    // Secretary creates the form
    Form* form = _secretary->createForm(SubscriptionToCourse);
    SubscriptionToCourseForm* subForm = dynamic_cast<SubscriptionToCourseForm*>(form);
    
    if (subForm)
    {
        // Fill the form
        subForm->setStudent(student);
        subForm->setCourse(course);
        
        // Sign and execute
        signForm(subForm);
        executeForm(subForm);
    }
    delete form;
}

void Headmaster::requestClassroom(Professor* professor)
{
    if (!professor || !_secretary)
    {
        std::cout << "Cannot process classroom request" << std::endl;
        return;
    }
    
    std::cout << "\n[MEDIATOR] " << professor->getName() 
              << " requests a new classroom" << std::endl;
    
    // Secretary creates the form
    Form* form = _secretary->createForm(NeedMoreClassRoom);
    
    if (form)
    {
        // Sign and execute
        signForm(form);
        executeForm(form);
        
        std::cout << "[MEDIATOR] New classroom created for " 
                  << professor->getName() << std::endl;
    }
    delete form;
}

void Headmaster::graduateStudent(Student* student, Course* course)
{
    if (!student || !course || !_secretary)
    {
        std::cout << "Cannot process graduation request" << std::endl;
        return;
    }
    
    std::cout << "\n[MEDIATOR] Processing graduation for " << student->getName() 
              << " from " << course->getName() << std::endl;
    
    // Secretary creates the form
    Form* form = _secretary->createForm(CourseFinished);
    CourseFinishedForm* gradForm = dynamic_cast<CourseFinishedForm*>(form);
    
    if (gradForm)
    {
        // Fill the form
        gradForm->setStudent(student);
        gradForm->setCourse(course);
        
        // Sign and execute
        signForm(gradForm);
        executeForm(gradForm);
    }
    delete form;
}

void Headmaster::teacherAssignToCourse(Professor* professor, Course* course)
{
    if (!professor || !course)
    {
        std::cout << "Cannot assign professor to course" << std::endl;
        return;
    }
    
    std::cout << "\n[MEDIATOR] Assigning " << professor->getName() 
              << " to teach " << course->getName() << std::endl;
    
    professor->assignCourse(course);
}

void Headmaster::bellRing()
{
    std::cout << "\n[MEDIATOR] BELL RINGS! Time for break/class change" << std::endl;
    // This will be expanded in ex04 with Observer pattern
}
