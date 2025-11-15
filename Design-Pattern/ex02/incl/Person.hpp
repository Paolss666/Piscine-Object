#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>

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

class Student : public Person
{
private:
    std::vector<class Course*> _subscribedCourse;

public:
    Student(std::string p_name);
    virtual ~Student();
    void attendClass(class Classroom* p_classroom);
    void exitClass();
    void graduate(class Course* p_course);
    const std::vector<class Course*>& getSubscribedCourses() const { return _subscribedCourse; }
    void subscribeToCourse(class Course* p_course);
};

class Professor : public Staff
{
private:
    class Course* _currentCourse;

public:
    Professor(std::string p_name);
    virtual ~Professor();
    void assignCourse(class Course* p_course);
    void doClass();
    void closeCourse();
    class Course* getCurrentCourse() const { return _currentCourse; }
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
    
public:
    Headmaster(std::string p_name);
    virtual ~Headmaster();
    void receiveForm(Form* p_form);
    void signForm(Form* p_form);
    void executeForm(Form* p_form);
};

#endif // PERSON_HPP
