#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>
#include <vector>
/* Position structure */
/* COMPOSITION -> Worker has-a Position and Statistic */
/* AGGREGATION -> Shovel has-a Workers (workers can exist independently) */
/* INHERITANCE -> Manager is-a Worker */

//COMPOSITION
struct Position
{
    int _x;
    int _y;
    int _z;

    Position() : _x(0), _y(0), _z(0) {};
    Position(int x, int y, int z) : _x(x), _y(y), _z(z) {};

};

struct Statistic
{
    int _level;
    int _exp;

    Statistic() : _level(0), _exp(0) {};
    Statistic(int level, int exp) : _level(level), _exp(exp) {};
};


class Worker;
class Workshop;

//INHERITANCE
class Tool
{
    protected:

    int _numberOfUses;
    Worker* _currentOwner;

    public:
    Tool(int use = 0) : _numberOfUses(use), _currentOwner(NULL) 
    {
        std::cout << "Tool created" << std::endl;
    };

    
    virtual ~Tool()
    {
        std::cout << "Tool destroyed" << std::endl;
    };
    virtual void use() = 0;
    void setOwner(Worker* owner) { _currentOwner = owner; };
    Worker* getOwner() const { return _currentOwner; };
    int getNumberOfUses() const { return _numberOfUses; };
};

//AGGREGATION
class Shovel : public Tool
{

    public:
    Shovel(int use = 0)
    : Tool(use)
    {
        std::cout << "Shovel created" << std::endl;

    };
    ~Shovel()
    {
        std::cout << "Shovel destroyed" << std::endl;
    };
    void use()
    {
        _numberOfUses++;
        std::cout << "Shovel used " << _numberOfUses << " times." << std::endl;
    };
};

class Hammer : public Tool
{

    public:
    Hammer(int use = 0)
    : Tool(use)
    {
        std::cout << "Hammer created" << std::endl;

    };
    ~Hammer()
    {
        std::cout << "Hammer destroyed" << std::endl;
    };
    void use()

    {
        _numberOfUses++;
        std::cout << "Hammer used " << _numberOfUses << " times." << std::endl;
    };
};

// class Workshop;

class Worker {
    private:
    Position _pos;
    Statistic _stat;
    std::vector<Tool*> _tools;
    std::vector<Workshop*> _workshops;

    public:
    std::vector<Tool*> getTools() const { return _tools; };
    void giveTool(Tool* tool)
    {
        if (tool)
        {
            if (tool->getOwner() != this && tool->getOwner() != NULL)
            {
                tool->getOwner()->takenTool(tool);
                std::cout << "Tool have already a owner, removing the current one." << std::endl;

            }
            _tools.push_back(tool);
            tool->setOwner(this);
            }
    }

    Tool* takenTool(Tool* tool)
    {
        std::vector<Tool*>::iterator it = _tools.begin();
        for (; it != _tools.end(); ++it)
        {
            if (*it == tool)
            {
                _tools.erase(it);
                tool->setOwner(NULL);
                return tool;
            }
        }
        return NULL;
    }
    Worker(): _pos(), _stat(), _tools()
    {
        std::cout << "Worker created" << std::endl;
    };

    Worker(const Position &pos, const Statistic &stat): _pos(pos), _stat(stat), _tools()
    {
        std::cout << "Worker created with position and stats" << std::endl;
    };

    Worker(int x, int y, int z, int level, int exp) : _pos(), _stat(), _tools()
    {
        _pos._x = x;
        _pos._y = y;
        _pos._z = z;
        _stat._level = level;
        _stat._exp = exp;
        std::cout << "Worker created with parameters" << std::endl;
    };

    ~Worker()
    {
        for (size_t i = 0; i < _workshops.size(); ++i)
        {
            leaveWorkShop(*_workshops[i]);
        }
        for (size_t i = 0; i < _tools.size(); ++i)
        {
            if (_tools[i]){
            _tools[i]->setOwner(NULL);
            }
        }
        std::cout << "Worker destroyed" << std::endl;
    };

    void joinWorkShop(Workshop &workshop);
    void leaveWorkShop(Workshop &workshop);
    Position getPosition() const { return _pos; };
    Statistic getStatistic() const { return _stat; };
    void setPosition(int x, int y, int z) { _pos._x = x; _pos._y = y; _pos._z = z; };

    void work()
    {
        std::cout << "Working..." << std::endl;
        if (_workshops.empty())
        {
            std::cout << "No workshop to work in." << std::endl;
            return;
        }
        std::cout << "Working in " << _workshops.size() << " workshops." << std::endl;
    }

    void displayWorker() const 
    {
     std::cout << " displayWorker() called" << std::endl;
        std::cout << "Position: (" << _pos._x << ", " << _pos._y << ", " << _pos._z << ")" << std::endl;
        std::cout << "Stats: Level " << _stat._level << ", Experience " << _stat._exp << std::endl;
        std::cout << "Tools: " << _tools.size() << std::endl;
        std::cout << "Workshops: " << _workshops.size() << std::endl;
    }
    // void doWork();
};

// association methods
inline void Worker::joinWorkShop(Workshop &workshop)
{
    std::vector<Workshop*>::iterator it = _workshops.begin();
    for (; it != _workshops.end(); ++it)
    {
        if (*it == &workshop)
        {
            std::cout << "Already in this workshop" << std::endl;
            return;
        }
    }
    _workshops.push_back(&workshop);
    // workshop.registerWorker(*this);
    std::cout << "Joined workshop" << std::endl;
}


inline void Worker::leaveWorkShop(Workshop &workshop)
{
    std::vector<Workshop*>::iterator it = _workshops.begin();
    for (; it != _workshops.end(); ++it)
    {
        if (*it == &workshop)
        {
            _workshops.erase(it);
            // workshop.releaseWorker(*this);
            std::cout << "Left workshop" << std::endl;
            return;
        }
    }
    std::cout << "Not in this workshop" << std::endl;
}


class Workshop 
{
    private:
    std::vector<Worker*> _workers;

    public:
    Workshop() : _workers()
    {
        std::cout << "Workshop created" << std::endl;
    };
    ~Workshop()
    {
        std::vector<Worker*>::iterator it = _workers.begin();
        for (; it != _workers.end(); ++it)
        {
            (*it)->leaveWorkShop(*this);
        }
        _workers.clear();
        std::cout << "Workshop destroyed" << std::endl;
    };

    
    void registerWorker(Worker &worker)
    {
        std::vector<Worker*>::iterator it = _workers.begin();
        for (; it != _workers.end(); ++it)
        {
            if (*it == &worker)
            {
                std::cout << "Worker already in the workshop" << std::endl;
                return;
            }
        }
        _workers.push_back(&worker);
        worker.joinWorkShop(*this);
        std::cout << "Worker registered in the workshop" << std::endl;
    }

    void releaseWorker(Worker &worker)
    {
        std::vector<Worker*>::iterator it = _workers.begin();
        for (; it != _workers.end(); ++it)
        {
            if (*it == &worker)
            {
                _workers.erase(it);
                worker.leaveWorkShop(*this);
                std::cout << "Worker released from the workshop" << std::endl;
                return;
            }
        }
        std::cout << "Worker not found in the workshop" << std::endl;
    }

    std::vector<Worker*> getWorkers() const { return _workers; };
    size_t getWorkersCount() const { return _workers.size(); };
    void executeWork()
    {
        std::cout << "Workshop executing work with " << _workers.size() << " workers." << std::endl;
        for (size_t i = 0; i < _workers.size(); ++i)
        {
            _workers[i]->work();
        }
    }
};



// void work(){
//     std::cout << "Working..." << std::endl;
//     if (work)
// }
// std::vector<Tool *> getAllToolsOfWorker(const Worker &worker)
// {
    // return worker.getTools();
// }
// 

#endif