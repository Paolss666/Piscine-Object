#include "../incl/School.hpp"
#include "../incl/Form.hpp"
#include <iostream>

School::School() : _classesHeld(0)
{
    std::cout << "=== Initializing School (Facade) ===" << std::endl;
    
    // Create core staff
    _headmaster = new Headmaster("Mr. Principal");
    _secretary = new Secretary("Ms. Administrator");
    _headmaster->setSecretary(_secretary);
    
    // Create basic infrastructure
    createInitialRooms();
    
    std::cout << "School initialized successfully!" << std::endl;
}

School::~School()
{
    delete _headmaster;
    delete _secretary;
    // Note: Students, Professors, Courses, and Rooms are managed by singletons
}

void School::createInitialRooms()
{
    // Create essential rooms
    _courtyard = new Courtyard();
    Classroom* class1 = new Classroom();
    Classroom* class2 = new Classroom();
    Classroom* class3 = new Classroom();
    StaffRestRoom* staffRoom = new StaffRestRoom();
    SecretarialOffice* secOffice = new SecretarialOffice();
    HeadmasterOffice* headOffice = new HeadmasterOffice();
    
    // Register rooms
    RoomList& roomList = RoomList::getInstance();
    roomList.add(_courtyard);
    roomList.add(class1);
    roomList.add(class2);
    roomList.add(class3);
    roomList.add(staffRoom);
    roomList.add(secOffice);
    roomList.add(headOffice);
}

void School::runDayRoutine()
{
    std::cout << "\n======================================" << std::endl;
    std::cout << "     SCHOOL DAY ROUTINE STARTING" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // Morning
    std::cout << "\n--- 8:00 AM: First Period ---" << std::endl;
    launchClasses();
    
    std::cout << "\n--- 10:00 AM: Morning Break ---" << std::endl;
    requestRingBell();
    moveEveryoneToCourtyard();
    
    std::cout << "\n--- 10:30 AM: Second Period ---" << std::endl;
    requestRingBell();
    launchClasses();
    
    std::cout << "\n--- 12:30 PM: Lunch Break ---" << std::endl;
    requestRingBell();
    std::cout << "Everyone goes to lunch..." << std::endl;
    
    std::cout << "\n--- 1:30 PM: Third Period ---" << std::endl;
    requestRingBell();
    launchClasses();
    
    std::cout << "\n--- 3:30 PM: Afternoon Break ---" << std::endl;
    requestRingBell();
    moveEveryoneToCourtyard();
    
    std::cout << "\n--- 4:00 PM: Fourth Period ---" << std::endl;
    requestRingBell();
    launchClasses();
    
    std::cout << "\n--- 5:30 PM: End of School Day ---" << std::endl;
    requestRingBell();
    
    std::cout << "\n======================================" << std::endl;
    std::cout << "       SCHOOL DAY COMPLETED" << std::endl;
    std::cout << "======================================" << std::endl;
}

void School::launchClasses()
{
    std::cout << "[FACADE] Launching classes..." << std::endl;
    _classesHeld++;
    
    // Get all professors and students
    std::vector<Professor*> professors = getProfessors();
    std::vector<Student*> students = getStudents();
    
    // Make sure professors have courses
    assignProfessorsToCourses();
    
    // Make sure students are enrolled
    enrollStudentsInCourses();
    
    // Start teaching
    for (size_t i = 0; i < professors.size(); ++i)
    {
        if (professors[i]->getCurrentCourse())
        {
            professors[i]->doClass();
            
            // Find available classroom for this course
            Classroom* classroom = RoomList::getInstance().getAvailableClassroom();
            if (!classroom)
            {
                std::cout << "  No classroom available, requesting new one..." << std::endl;
                _headmaster->requestClassroom(professors[i]);
                classroom = RoomList::getInstance().getAvailableClassroom();
            }
            
            if (classroom)
            {
                classroom->assignCourse(professors[i]->getCurrentCourse());
                
                // Move students to classroom
                const std::vector<Student*>& courseStudents = 
                    professors[i]->getCurrentCourse()->getStudents();
                for (size_t j = 0; j < courseStudents.size(); ++j)
                {
                    courseStudents[j]->attendClass(classroom);
                }
            }
        }
    }
    
    std::cout << "  Classes launched successfully (Session #" << _classesHeld << ")" << std::endl;
}

void School::requestRingBell()
{
    std::cout << "[FACADE] Requesting bell ring..." << std::endl;
    _headmaster->bellRing();
}

void School::recruteProfessor(const std::string& name)
{
    std::cout << "[FACADE] Recruiting professor: " << name << std::endl;
    Professor* newProf = new Professor(name);
    StaffList::getInstance().add(newProf);
    
    // Create a course for the new professor
    std::string courseName = name + "'s Course";
    _headmaster->requestCourseCreation(newProf, courseName);
}

void School::recruteStudent(const std::string& name)
{
    std::cout << "[FACADE] Recruiting student: " << name << std::endl;
    Student* newStudent = new Student(name);
    StudentList::getInstance().add(newStudent);
    
    // Try to enroll in an available course
    const std::vector<Course*>& courses = CourseList::getInstance().getAll();
    for (size_t i = 0; i < courses.size(); ++i)
    {
        if (!courses[i]->isFull())
        {
            _headmaster->requestCourseSubscription(newStudent, courses[i]);
            break;
        }
    }
}

Course* School::getCourse(const std::string& p_name)
{
    return CourseList::getInstance().getByName(p_name);
}

std::vector<Student*> School::getStudents()
{
    const std::vector<Student*>& students = StudentList::getInstance().getAll();
    return std::vector<Student*>(students.begin(), students.end());
}

std::vector<Professor*> School::getProfessors()
{
    std::vector<Professor*> professors;
    const std::vector<Staff*>& staff = StaffList::getInstance().getAll();
    
    for (size_t i = 0; i < staff.size(); ++i)
    {
        Professor* prof = dynamic_cast<Professor*>(staff[i]);
        if (prof)
            professors.push_back(prof);
    }
    
    return professors;
}

void School::graduationCeremony()
{
    std::cout << "\n[FACADE] === GRADUATION CEREMONY ===" << std::endl;
    
    const std::vector<Student*>& students = StudentList::getInstance().getAll();
    const std::vector<Course*>& courses = CourseList::getInstance().getAll();
    
    int graduatedCount = 0;
    
    for (size_t i = 0; i < students.size(); ++i)
    {
        const std::vector<Course*>& studentCourses = students[i]->getSubscribedCourses();
        
        for (size_t j = 0; j < studentCourses.size(); ++j)
        {
            // Check if student completed enough classes (using _classesHeld as indicator)
            if (_classesHeld >= studentCourses[j]->getNumberOfClassToGraduate())
            {
                std::cout << "  Graduating " << students[i]->getName() 
                          << " from " << studentCourses[j]->getName() << std::endl;
                _headmaster->graduateStudent(students[i], studentCourses[j]);
                graduatedCount++;
            }
        }
    }
    
    if (graduatedCount > 0)
    {
        std::cout << "  Total graduates: " << graduatedCount << std::endl;
        std::cout << "  Congratulations to all graduates!" << std::endl;
    }
    else
    {
        std::cout << "  No students ready for graduation yet." << std::endl;
        std::cout << "  Classes held: " << _classesHeld 
                  << " (need " << (courses.empty() ? 10 : courses[0]->getNumberOfClassToGraduate())
                  << " for graduation)" << std::endl;
    }
}

void School::enrollStudentsInCourses()
{
    const std::vector<Student*>& students = StudentList::getInstance().getAll();
    const std::vector<Course*>& courses = CourseList::getInstance().getAll();
    
    for (size_t i = 0; i < students.size(); ++i)
    {
        if (students[i]->getSubscribedCourses().empty() && !courses.empty())
        {
            // Find a course with space
            for (size_t j = 0; j < courses.size(); ++j)
            {
                if (!courses[j]->isFull())
                {
                    _headmaster->requestCourseSubscription(students[i], courses[j]);
                    break;
                }
            }
        }
    }
}

void School::assignProfessorsToCourses()
{
    std::vector<Professor*> professors = getProfessors();
    const std::vector<Course*>& courses = CourseList::getInstance().getAll();
    
    for (size_t i = 0; i < professors.size(); ++i)
    {
        if (!professors[i]->getCurrentCourse())
        {
            // Find unassigned course or create new one
            bool assigned = false;
            for (size_t j = 0; j < courses.size(); ++j)
            {
                if (!courses[j]->getResponsable())
                {
                    _headmaster->teacherAssignToCourse(professors[i], courses[j]);
                    assigned = true;
                    break;
                }
            }
            
            if (!assigned)
            {
                // Create new course for this professor
                std::string courseName = "Course by " + professors[i]->getName();
                _headmaster->requestCourseCreation(professors[i], courseName);
            }
        }
    }
}

void School::moveEveryoneToCourtyard()
{
    std::cout << "  Everyone gathers in the courtyard for break" << std::endl;
    
    const std::vector<Student*>& students = StudentList::getInstance().getAll();
    for (size_t i = 0; i < students.size(); ++i)
    {
        if (students[i]->room() != _courtyard)
        {
            if (students[i]->room())
                students[i]->room()->exit(students[i]);
            _courtyard->enter(students[i]);
        }
    }
}
