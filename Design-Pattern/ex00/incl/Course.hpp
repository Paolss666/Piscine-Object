#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>

// Forward declarations
class Student;
class Professor;

class Course
{
private:
	std::string _name;
	Professor* _responsable;
	std::vector<Student*> _students;
	int _numberOfClassToGraduate;
	int _maximumNumberOfStudent;

public:
	Course(std::string p_name);
	
	void assign(Professor* p_professor);
	void subscribe(Student* p_student);
	
	const std::string& name() const;
	Professor* responsable() const;
	const std::vector<Student*>& students() const;
	int numberOfClassToGraduate() const;
	int maximumNumberOfStudent() const;
};

#endif