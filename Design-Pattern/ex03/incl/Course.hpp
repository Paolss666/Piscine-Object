#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>

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
    ~Course();
    void assign(Professor* p_professor);
    void subscribe(Student* p_student);
    
    const std::string& getName() const { return _name; }
    Professor* getResponsable() const { return _responsable; }
    const std::vector<Student*>& getStudents() const { return _students; }
    int getNumberOfClassToGraduate() const { return _numberOfClassToGraduate; }
    void setNumberOfClassToGraduate(int num) { _numberOfClassToGraduate = num; }
    int getMaximumNumberOfStudent() const { return _maximumNumberOfStudent; }
    void setMaximumNumberOfStudent(int num) { _maximumNumberOfStudent = num; }
    bool isFull() const;
    void removeStudent(Student* p_student);
};

#endif // COURSE_HPP
