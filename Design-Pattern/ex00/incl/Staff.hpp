#ifndef STAFF_HPP
#define STAFF_HPP

#include "Person.hpp"
#include <vector>

// Forward declarations
class Form;
class Course;
class FormType;

class Staff : public Person
{
private:

public:
	Staff(std::string p_name);
	void sign(Form* p_form);
};

class Headmaster : public Staff
{
private:
	std::vector<Form*> _formToValidate;
	
public:
	Headmaster(std::string p_name);
	void receiveForm(Form* p_form);
};

class Secretary : public Staff
{
private:

public:
	Secretary(std::string p_name);
	Form* createForm(FormType p_formType);
	void archiveForm();
};

class Professor : public Staff
{
private:
	Course* _currentCourse;

public:
	Professor(std::string p_name);
	void assignCourse(Course* p_course);
	void doClass();
	void closeCourse();
};

#endif