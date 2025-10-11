#ifndef ROOM_HPP
#define ROOM_HPP

#include <vector>

// Forward declarations
class Person;
class Course;
class Form;

class Room
{
private:
	long long _ID;
	std::vector<Person*> _occupants;

public:
	Room();
	virtual ~Room() = default;
	
	bool canEnter(Person* p_person);
	void enter(Person* p_person);
	void exit(Person* p_person);
	void printOccupant();
};

class Classroom : public Room
{
private:
	Course* _currentCourse;

public:
	Classroom();
	void assignCourse(Course* p_course);
};

class SecretarialOffice : public Room
{
private:
	std::vector<Form*> _archivedForms;

public:
	SecretarialOffice();
};

class HeadmasterOffice : public Room
{
private:

public:
	HeadmasterOffice();
};

class StaffRestRoom : public Room
{
private:

public:
	StaffRestRoom();
};

class Courtyard : public Room
{
private:

public:
	Courtyard();
};

#endif