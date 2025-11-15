#include "../include/SimulationManager.hpp"
#include "../include/DijkstraPathfinding.hpp"
#include <algorithm>
#include <cmath>

SimulationManager* SimulationManager::_instance = NULL;

SimulationManager::SimulationManager() 
    : _network(NULL), _pathfinder(NULL), _timeStepMinutes(5) {
}

SimulationManager::~SimulationManager() {
    // Don't delete network and trains - they're managed externally
    if (_pathfinder != NULL) {
        delete _pathfinder;
    }
}

SimulationManager* SimulationManager::getInstance() {
    if (_instance == NULL) {
        _instance = new SimulationManager();
    }
    return _instance;
}

void SimulationManager::destroyInstance() {
    if (_instance != NULL) {
        delete _instance;
        _instance = NULL;
    }
}

void SimulationManager::setNetwork(RailwayNetwork* network) {
    _network = network;
}

void SimulationManager::addTrain(Train* train) {
    if (train != NULL) {
        _trains.push_back(train);
    }
}

void SimulationManager::setPathfindingStrategy(IPathfindingStrategy* strategy) {
    if (_pathfinder != NULL) {
        delete _pathfinder;
    }
    _pathfinder = strategy;
}

void SimulationManager::initialize() {
    if (_pathfinder == NULL) {
        _pathfinder = new DijkstraPathfinding();
    }
    
    // Find paths for all trains
    for (size_t i = 0; i < _trains.size(); ++i) {
        Train* train = _trains[i];
        std::vector<Node*> path = _pathfinder->findPath(
            train->getDeparture(),
            train->getDestination()
        );
        
        if (!path.empty()) {
            train->setPath(path);
            
            // Add train to first rail
            if (path.size() >= 2) {
                Rail* firstRail = path[0]->getRailTo(path[1]);
                if (firstRail != NULL) {
                    firstRail->addTrain(train);
                }
            }
        }
    }
    
    // Find earliest departure time
    if (!_trains.empty()) {
        _currentTime = _trains[0]->getDepartureTime();
        for (size_t i = 1; i < _trains.size(); ++i) {
            if (_trains[i]->getDepartureTime() < _currentTime) {
                _currentTime = _trains[i]->getDepartureTime();
            }
        }
    }
}

bool SimulationManager::isComplete() const {
    for (size_t i = 0; i < _trains.size(); ++i) {
        if (!_trains[i]->hasArrived()) {
            return false;
        }
    }
    return true;
}
