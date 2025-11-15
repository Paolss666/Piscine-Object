#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>
#include "observer.hpp"

class Room;
class Form;

class Person
{
private:
    std::string _name;
    Room* _currentRoom;
    
public:
    Person(std::string p_name);
    virtual ~Person();
    Room* room() { return _currentRoom; }
    void setRoom(Room* room) { _currentRoom = room; }
    const std::string& getName() const { return _name; }
};

class Staff : public Person
{
public:
    Staff(std::string p_name);
    virtual ~Staff();
    void sign(Form* p_form);
};

class Student : public Person, public IObserver
{
private:
    std::vector<class Course*> _subscribedCourse;
    bool _inClass;

public:
    Student(std::string p_name);
    virtual ~Student();
    void attendClass(class Classroom* p_classroom);
    void exitClass();
    void graduate(class Course* p_course);
    const std::vector<class Course*>& getSubscribedCourses() const { return _subscribedCourse; }
    void subscribeToCourse(class Course* p_course);
    
    // Observer pattern
    virtual void update(Event event);
    bool isInClass() const { return _inClass; }
};

class Professor : public Staff, public IObserver
{
private:
    class Course* _currentCourse;
    bool _teaching;

public:
    Professor(std::string p_name);
    virtual ~Professor();
    void assignCourse(class Course* p_course);
    void doClass();
    void closeCourse();
    class Course* getCurrentCourse() const { return _currentCourse; }
    
    // Observer pattern
    virtual void update(Event event);
    bool isTeaching() const { return _teaching; }
};

class Secretary : public Staff
{
public:
    Secretary(std::string p_name);
    virtual ~Secretary();
    Form* createForm(int p_formType);
    void archiveForm(Form* p_form);
};

class Headmaster : public Staff
{
private:
    std::vector<Form*> _formToValidate;
    class Secretary* _secretary;
    
public:
    Headmaster(std::string p_name);
    virtual ~Headmaster();
    void receiveForm(Form* p_form);
    void signForm(Form* p_form);
    void executeForm(Form* p_form);
    
    // Mediator Pattern methods
    void setSecretary(class Secretary* secretary) { _secretary = secretary; }
    void requestCourseCreation(Professor* professor, const std::string& courseName);
    void requestCourseSubscription(Student* student, Course* course);
    void requestClassroom(Professor* professor);
    void graduateStudent(Student* student, Course* course);
    void teacherAssignToCourse(Professor* professor, Course* course);
    void bellRing();
};

#endif // PERSON_HPP
