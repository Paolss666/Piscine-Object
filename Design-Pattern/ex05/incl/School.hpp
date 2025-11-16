#ifndef SCHOOL_HPP
#define SCHOOL_HPP

#include <string>
#include <vector>
#include "../incl/Person.hpp"
#include "../incl/Course.hpp"
#include "../incl/Room.hpp"
#include "../incl/singletons.hpp"
#include "../incl/observer.hpp"

// Facade Pattern - Simplifies complex school operations
class School
{
private:
    Headmaster* _headmaster;
    Secretary* _secretary;
    Courtyard* _courtyard;
    int _classesHeld;
    
public:
    School();
    ~School();
    
    // Facade methods - hide complexity
    void runDayRoutine();
    void launchClasses();
    void requestRingBell();
    void recruteProfessor(const std::string& name);
    void recruteStudent(const std::string& name);
    Course* getCourse(const std::string& p_name);
    std::vector<Student*> getStudents();
    std::vector<Professor*> getProfessors();
    Headmaster* getHeadmaster() { return _headmaster; }
    Secretary* getSecretary() { return _secretary; }
    void graduationCeremony();
    
private:
    // Helper methods
    void enrollStudentsInCourses();
    void assignProfessorsToCourses();
    void createInitialRooms();
    void moveEveryoneToCourtyard();
};

#endif // SCHOOL_HPP
