
#ifndef SINGLETONS_HPP
#define SINGLETONS_HPP

#include "Singleton.hpp"
#include "Student.hpp"
#include "Staff.hpp"
#include "Course.hpp"
#include "Room.hpp"

// Type aliases for cleaner usage
using StudentList = Singleton<Student>;
using StaffList = Singleton<Staff>;
using CourseList = Singleton<Course>;
using RoomList = Singleton<Room>;

#endif