#ifndef SIMULATIONMANAGER_HPP
#define SIMULATIONMANAGER_HPP

#include "RailwayNetwork.hpp"
#include "Train.hpp"
#include "IPathfindingStrategy.hpp"
#include "ISubject.hpp"
#include <vector>

/**
 * @class SimulationManager
 * @brief Singleton Pattern - Manages the entire simulation
 * 
 * Central controller for the railway simulation.
 * Implements Singleton to ensure only one simulation instance.
 * SOLID: Single Responsibility - coordinates simulation
 */
class SimulationManager : public ISubject {
private:
    static SimulationManager* _instance;
    
    RailwayNetwork* _network;
    std::vector<Train*> _trains;
    IPathfindingStrategy* _pathfinder;
    Time _currentTime;
    int _timeStepMinutes;
    
    // Private constructor for Singleton
    SimulationManager();
    
    // Prevent copying
    SimulationManager(const SimulationManager&);
    SimulationManager& operator=(const SimulationManager&);

public:
    ~SimulationManager();
    
    // Singleton access
    static SimulationManager* getInstance();
    static void destroyInstance();
    
    // Initialization
    void setNetwork(RailwayNetwork* network);
    void addTrain(Train* train);
    void setPathfindingStrategy(IPathfindingStrategy* strategy);
    
    // Simulation control
    void initialize();
    void run();
    void step();
    bool isComplete() const;
    
    // Getters
    RailwayNetwork* getNetwork() const { return _network; }
    const std::vector<Train*>& getTrains() const { return _trains; }
    const Time& getCurrentTime() const { return _currentTime; }
    int getTimeStepMinutes() const { return _timeStepMinutes; }
    
    // Setters
    void setTimeStepMinutes(int minutes) { _timeStepMinutes = minutes; }
    
private:
    void updateTrains();
    void checkCollisions();
    void handleTrainInteractions();
};

#endif // SIMULATIONMANAGER_HPP
