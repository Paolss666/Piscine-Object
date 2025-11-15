#ifndef FORM_HPP
#define FORM_HPP

#include <string>

class Student;
class Course;
class Room;
class Headmaster;

enum FormType
{
    CourseFinished,
    NeedMoreClassRoom,
    NeedCourseCreation,
    SubscriptionToCourse
};

class Form
{
private:
    FormType _formType;
    bool _isSigned;

public:
    Form(FormType p_formType);
    virtual ~Form();
    virtual void execute() = 0;
    
    FormType getFormType() const { return _formType; }
    bool isSigned() const { return _isSigned; }
    void sign() { _isSigned = true; }
};

class CourseFinishedForm : public Form
{
private:
    Student* _student;
    Course* _course;

public:
    CourseFinishedForm();
    virtual ~CourseFinishedForm();
    virtual void execute();
    
    void setStudent(Student* student) { _student = student; }
    void setCourse(Course* course) { _course = course; }
    Student* getStudent() const { return _student; }
    Course* getCourse() const { return _course; }
};

class NeedMoreClassRoomForm : public Form
{
private:
    Room* _newRoom;

public:
    NeedMoreClassRoomForm();
    virtual ~NeedMoreClassRoomForm();
    virtual void execute();
    
    void setNewRoom(Room* room) { _newRoom = room; }
    Room* getNewRoom() const { return _newRoom; }
};

class NeedCourseCreationForm : public Form
{
private:
    std::string _courseName;
    Course* _newCourse;

public:
    NeedCourseCreationForm();
    virtual ~NeedCourseCreationForm();
    virtual void execute();
    
    void setCourseName(const std::string& name) { _courseName = name; }
    void setNewCourse(Course* course) { _newCourse = course; }
    const std::string& getCourseName() const { return _courseName; }
    Course* getNewCourse() const { return _newCourse; }
};

class SubscriptionToCourseForm : public Form
{
private:
    Student* _student;
    Course* _course;

public:
    SubscriptionToCourseForm();
    virtual ~SubscriptionToCourseForm();
    virtual void execute();
    
    void setStudent(Student* student) { _student = student; }
    void setCourse(Course* course) { _course = course; }
    Student* getStudent() const { return _student; }
    Course* getCourse() const { return _course; }
};

#endif // FORM_HPP
