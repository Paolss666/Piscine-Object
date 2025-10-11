#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

// Forward declarations
class Room;

class Person
{
private:
	std::string _name;
	Room* _currentRoom;

public:
	Person(std::string p_name);
	Room* room();
	const std::string& name() const;
};

#endif