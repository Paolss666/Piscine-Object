#include "../incl/singletons.hpp"
#include "../ex00/incl/Student.hpp"
#include "../ex00/incl/Staff.hpp"
#include "../ex00/incl/Course.hpp"
#include "../ex00/incl/Room.hpp"
#include <iostream>
#include <thread>

void testThreadSafety()
{
	// Test that getInstance returns the same instance across threads
	StudentList* list1 = StudentList::getInstance();
	StudentList* list2 = StudentList::getInstance();
	
	std::cout << "Thread " << std::this_thread::get_id() 
			  << " - Same instance: " << (list1 == list2 ? "YES" : "NO") << std::endl;
}

int main()
{
	std::cout << "=== Exercise 01: Singleton Pattern ===" << std::endl << std::endl;

	// Test 1: Get singleton instances
	std::cout << "Test 1: Getting singleton instances" << std::endl;
	StudentList* studentList = StudentList::getInstance();
	StaffList* staffList = StaffList::getInstance();
	CourseList* courseList = CourseList::getInstance();
	RoomList* roomList = RoomList::getInstance();
	std::cout << "✓ All singleton instances created" << std::endl << std::endl;

	// Test 2: Verify it's the same instance
	std::cout << "Test 2: Verify singleton uniqueness" << std::endl;
	StudentList* studentList2 = StudentList::getInstance();
	std::cout << "Same StudentList instance: " 
			  << (studentList == studentList2 ? "YES ✓" : "NO ✗") << std::endl << std::endl;

	// Test 3: Add students
	std::cout << "Test 3: Adding students" << std::endl;
	Student* alice = new Student("Alice");
	Student* bob = new Student("Bob");
	Student* charlie = new Student("Charlie");
	
	studentList->add(alice);
	studentList->add(bob);
	studentList->add(charlie);
	
	std::cout << "Added " << studentList->size() << " students" << std::endl;
	std::cout << "Students: ";
	for (size_t i = 0; i < studentList->size(); ++i)
	{
		std::cout << studentList->get(i)->name();
		if (i < studentList->size() - 1)
			std::cout << ", ";
	}
	std::cout << std::endl << std::endl;

	// Test 4: Add staff
	std::cout << "Test 4: Adding staff members" << std::endl;
	Professor* profSmith = new Professor("Prof. Smith");
	Professor* profJones = new Professor("Prof. Jones");
	Headmaster* headmaster = new Headmaster("Dr. Anderson");
	Secretary* secretary = new Secretary("Ms. Williams");
	
	staffList->add(profSmith);
	staffList->add(profJones);
	staffList->add(headmaster);
	staffList->add(secretary);
	
	std::cout << "Added " << staffList->size() << " staff members" << std::endl << std::endl;

	// Test 5: Add courses
	std::cout << "Test 5: Adding courses" << std::endl;
	Course* math = new Course("Mathematics");
	Course* physics = new Course("Physics");
	Course* chemistry = new Course("Chemistry");
	
	courseList->add(math);
	courseList->add(physics);
	courseList->add(chemistry);
	
	std::cout << "Added " << courseList->size() << " courses: ";
	for (size_t i = 0; i < courseList->size(); ++i)
	{
		std::cout << courseList->get(i)->name();
		if (i < courseList->size() - 1)
			std::cout << ", ";
	}
	std::cout << std::endl << std::endl;

	// Test 6: Add rooms
	std::cout << "Test 6: Adding rooms" << std::endl;
	Classroom* room101 = new Classroom();
	Classroom* room102 = new Classroom();
	StaffRestRoom* restroom = new StaffRestRoom();
	Courtyard* courtyard = new Courtyard();
	
	roomList->add(room101);
	roomList->add(room102);
	roomList->add(restroom);
	roomList->add(courtyard);
	
	std::cout << "Added " << roomList->size() << " rooms" << std::endl << std::endl;

	// Test 7: Retrieve elements
	std::cout << "Test 7: Retrieving elements by index" << std::endl;
	try
	{
		Student* firstStudent = studentList->get(0);
		std::cout << "First student: " << firstStudent->name() << " ✓" << std::endl;
		
		Course* secondCourse = courseList->get(1);
		std::cout << "Second course: " << secondCourse->name() << " ✓" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 8: Test out of range
	std::cout << "Test 8: Testing out of range access" << std::endl;
	try
	{
		studentList->get(999);
		std::cout << "✗ Should have thrown an exception!" << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "✓ Correctly threw exception: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	// Test 9: Thread safety
	std::cout << "Test 9: Testing thread safety" << std::endl;
	std::thread t1(testThreadSafety);
	std::thread t2(testThreadSafety);
	std::thread t3(testThreadSafety);
	
	t1.join();
	t2.join();
	t3.join();
	std::cout << std::endl;

	// Test 10: GetAll method
	std::cout << "Test 10: Getting all elements" << std::endl;
	const std::vector<Student*>& allStudents = studentList->getAll();
	std::cout << "Total students via getAll(): " << allStudents.size() << std::endl;
	for (const auto& student : allStudents)
		std::cout << "  - " << student->name() << std::endl;
	
	std::cout << std::endl << "=== All tests completed successfully! ===" << std::endl;

	// Cleanup (in real scenario, consider smart pointers)
	delete alice;
	delete bob;
	delete charlie;
	delete profSmith;
	delete profJones;
	delete headmaster;
	delete secretary;
	delete math;
	delete physics;
	delete chemistry;
	delete room101;
	delete room102;
	delete restroom;
	delete courtyard;

	return 0;
}