#include "Course.hpp"
#include "Person.hpp"
#include <algorithm>
#include <iostream>

Course::Course(std::string p_name) : 
    _name(p_name), 
    _responsable(NULL),
    _numberOfClassToGraduate(10),
    _maximumNumberOfStudent(30)
{
}

Course::~Course()
{
}

void Course::assign(Professor* p_professor)
{
    _responsable = p_professor;
}

void Course::subscribe(Student* p_student)
{
    if (!p_student || isFull())
        return;
        
    if (std::find(_students.begin(), _students.end(), p_student) == _students.end())
    {
        _students.push_back(p_student);
        std::cout << p_student->getName() << " subscribed to " << _name << std::endl;
    }
}

bool Course::isFull() const
{
    return static_cast<int>(_students.size()) >= _maximumNumberOfStudent;
}

void Course::removeStudent(Student* p_student)
{
    if (!p_student)
        return;
        
    std::vector<Student*>::iterator it = std::find(_students.begin(), 
                                                   _students.end(), 
                                                   p_student);
    if (it != _students.end())
    {
        _students.erase(it);
    }
}
