#include "../incl/Room.hpp"
#include "../incl/Person.hpp"
#include "../incl/Course.hpp"
#include "../incl/Form.hpp"
#include <iostream>
#include <algorithm>

int Room::_nextID = 0;

// Room implementation
Room::Room() : _id(_nextID++) {}
Room::~Room() {}

bool Room::canEnter(Person* p_person)
{
    return p_person != NULL;
}

void Room::enter(Person* p_person)
{
    if (p_person && canEnter(p_person))
    {
        _occupants.push_back(p_person);
        p_person->setRoom(this);
    }
}

void Room::exit(Person* p_person)
{
    if (!p_person)
        return;
        
    std::vector<Person*>::iterator it = std::find(_occupants.begin(), 
                                                  _occupants.end(), 
                                                  p_person);
    if (it != _occupants.end())
    {
        _occupants.erase(it);
        p_person->setRoom(NULL);
    }
}

void Room::printOccupant()
{
    std::cout << "Room " << _id << " occupants:" << std::endl;
    for (size_t i = 0; i < _occupants.size(); ++i)
    {
        std::cout << "  - " << _occupants[i]->getName() << std::endl;
    }
}

// Classroom implementation
Classroom::Classroom() : Room(), _currentCourse(NULL) {}
Classroom::~Classroom() {}

void Classroom::assignCourse(Course* p_course)
{
    _currentCourse = p_course;
}

bool Classroom::canEnter(Person* p_person)
{
    if (!p_person)
        return false;
        
    // Check if person is a professor teaching this course or a student enrolled
    if (Professor* prof = dynamic_cast<Professor*>(p_person))
    {
        return prof->getCurrentCourse() == _currentCourse;
    }
    else if (Student* student = dynamic_cast<Student*>(p_person))
    {
        const std::vector<Course*>& courses = student->getSubscribedCourses();
        return std::find(courses.begin(), courses.end(), _currentCourse) != courses.end();
    }
    
    return false;
}

// SecretarialOffice implementation
SecretarialOffice::SecretarialOffice() : Room() {}
SecretarialOffice::~SecretarialOffice() 
{
    for (size_t i = 0; i < _archivedForms.size(); ++i)
        delete _archivedForms[i];
}

void SecretarialOffice::archiveForm(Form* p_form)
{
    if (p_form)
        _archivedForms.push_back(p_form);
}

bool SecretarialOffice::canEnter(Person* p_person)
{
    // Only staff can enter
    return dynamic_cast<Staff*>(p_person) != NULL;
}

// HeadmasterOffice implementation
HeadmasterOffice::HeadmasterOffice() : Room() {}
HeadmasterOffice::~HeadmasterOffice() {}

bool HeadmasterOffice::canEnter(Person* p_person)
{
    // Everyone can enter the headmaster office
    return p_person != NULL;
}

// StaffRestRoom implementation
StaffRestRoom::StaffRestRoom() : Room() {}
StaffRestRoom::~StaffRestRoom() {}

bool StaffRestRoom::canEnter(Person* p_person)
{
    // Only staff can enter
    return dynamic_cast<Staff*>(p_person) != NULL;
}

// Courtyard implementation
Courtyard::Courtyard() : Room() {}
Courtyard::~Courtyard() {}

bool Courtyard::canEnter(Person* p_person)
{
    // Everyone can enter the courtyard
    return p_person != NULL;
}
