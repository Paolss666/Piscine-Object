#ifndef SINGLETONS_HPP
#define SINGLETONS_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../../ex00/incl/Person.hpp"
#include "../../ex00/incl/Room.hpp"
#include "../../ex00/incl/Course.hpp"

// Template Singleton class to avoid code repetition
template <typename T>
class ListSingleton
{
private:
    std::vector<T*> _list;
    
    // Private constructor and destructor for singleton
    ListSingleton() {}
    ~ListSingleton() 
    {
        for (typename std::vector<T*>::iterator it = _list.begin(); it != _list.end(); ++it)
            delete *it;
    }
    
    // Prevent copy and assignment
    ListSingleton(const ListSingleton&);
    ListSingleton& operator=(const ListSingleton&);
    
public:
    static ListSingleton& getInstance()
    {
        static ListSingleton instance;
        return instance;
    }
    
    void add(T* item)
    {
        if (item && std::find(_list.begin(), _list.end(), item) == _list.end())
            _list.push_back(item);
    }
    
    void remove(T* item)
    {
        typename std::vector<T*>::iterator it = std::find(_list.begin(), _list.end(), item);
        if (it != _list.end())
            _list.erase(it);
    }
    
    T* get(size_t index)
    {
        if (index < _list.size())
            return _list[index];
        return NULL;
    }
    
    T* getByName(const std::string& name)
    {
        for (typename std::vector<T*>::iterator it = _list.begin(); it != _list.end(); ++it)
        {
            if ((*it)->getName() == name)
                return *it;
        }
        return NULL;
    }
    
    const std::vector<T*>& getAll() const
    {
        return _list;
    }
    
    size_t size() const
    {
        return _list.size();
    }
};

// Specific typedefs for each list type
typedef ListSingleton<Student> StudentList;
typedef ListSingleton<Staff> StaffList;
typedef ListSingleton<Course> CourseList;

// Special implementation for RoomList (rooms don't have getName())
class RoomList
{
private:
    std::vector<Room*> _list;
    
    RoomList() {}
    ~RoomList()
    {
        for (std::vector<Room*>::iterator it = _list.begin(); it != _list.end(); ++it)
            delete *it;
    }
    
    RoomList(const RoomList&);
    RoomList& operator=(const RoomList&);
    
public:
    static RoomList& getInstance()
    {
        static RoomList instance;
        return instance;
    }
    
    void add(Room* item)
    {
        if (item && std::find(_list.begin(), _list.end(), item) == _list.end())
            _list.push_back(item);
    }
    
    void remove(Room* item)
    {
        std::vector<Room*>::iterator it = std::find(_list.begin(), _list.end(), item);
        if (it != _list.end())
            _list.erase(it);
    }
    
    Room* get(size_t index)
    {
        if (index < _list.size())
            return _list[index];
        return NULL;
    }
    
    Room* getById(int id)
    {
        for (std::vector<Room*>::iterator it = _list.begin(); it != _list.end(); ++it)
        {
            if ((*it)->getID() == id)
                return *it;
        }
        return NULL;
    }
    
    Classroom* getAvailableClassroom()
    {
        for (std::vector<Room*>::iterator it = _list.begin(); it != _list.end(); ++it)
        {
            Classroom* classroom = dynamic_cast<Classroom*>(*it);
            if (classroom && classroom->isEmpty())
                return classroom;
        }
        return NULL;
    }
    
    const std::vector<Room*>& getAll() const
    {
        return _list;
    }
    
    size_t size() const
    {
        return _list.size();
    }
};

#endif // SINGLETONS_HPP
