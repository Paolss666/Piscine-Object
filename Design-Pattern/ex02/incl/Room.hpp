#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>
#include <iostream>

class Person;
class Course;
class Form;

class Room
{
private:
    static int _nextID;
    int _id;
    std::vector<Person*> _occupants;

public:
    Room();
    virtual ~Room();
    virtual bool canEnter(Person* p_person);
    void enter(Person* p_person);
    void exit(Person* p_person);
    void printOccupant();
    int getID() const { return _id; }
    const std::vector<Person*>& getOccupants() const { return _occupants; }
    bool isEmpty() const { return _occupants.empty(); }
};

class Classroom : public Room
{
private:
    Course* _currentCourse;

public:
    Classroom();
    virtual ~Classroom();
    void assignCourse(Course* p_course);
    Course* getCurrentCourse() const { return _currentCourse; }
    virtual bool canEnter(Person* p_person);
};

class SecretarialOffice : public Room
{
private:
    std::vector<Form*> _archivedForms;

public:
    SecretarialOffice();
    virtual ~SecretarialOffice();
    void archiveForm(Form* p_form);
    virtual bool canEnter(Person* p_person);
};

class HeadmasterOffice : public Room
{
public:
    HeadmasterOffice();
    virtual ~HeadmasterOffice();
    virtual bool canEnter(Person* p_person);
};

class StaffRestRoom : public Room
{
public:
    StaffRestRoom();
    virtual ~StaffRestRoom();
    virtual bool canEnter(Person* p_person);
};

class Courtyard : public Room
{
public:
    Courtyard();
    virtual ~Courtyard();
    virtual bool canEnter(Person* p_person);
};

#endif // ROOM_HPP
