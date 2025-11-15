#include "../include/SimulationManager.hpp"
#include <cmath>
#include <algorithm>

// Additional methods for SimulationManager.cpp - append to previous file

void SimulationManager::step() {
    updateTrains();
    checkCollisions();
    handleTrainInteractions();
    
    _currentTime.addMinutes(_timeStepMinutes);
}

void SimulationManager::run() {
    const int maxSteps = 10000; // Safety limit
    int steps = 0;
    
    while (!isComplete() && steps < maxSteps) {
        step();
        steps++;
    }
}

void SimulationManager::updateTrains() {
    for (size_t i = 0; i < _trains.size(); ++i) {
        Train* train = _trains[i];
        
        // Check if train should depart
        if (train->getState() == STATE_STOPPED && 
            train->getCurrentTime() < train->getDepartureTime() &&
            _currentTime == train->getDepartureTime()) {
            train->setState(STATE_ACCELERATING);
        }
        
        train->setCurrentTime(_currentTime);
        
        if (train->getState() == STATE_STOPPED) {
            continue;
        }
        
        // Get current rail and speed limit
        const Position& pos = train->getPosition();
        if (pos.currentRail == NULL) {
            continue;
        }
        
        double speedLimit = pos.currentRail->getSpeedLimit();
        double currentSpeed = train->getCurrentSpeed();
        
        // Check for train ahead
        Train* trainAhead = pos.currentRail->getTrainAhead(train, pos.distanceOnRail);
        bool needBraking = false;
        
        if (trainAhead != NULL) {
            const Position& aheadPos = trainAhead->getPosition();
            double distance = aheadPos.distanceOnRail - pos.distanceOnRail;
            
            // Safety distance: 2 km
            if (distance < 2.0) {
                needBraking = true;
            }
        }
        
        // Update state and speed based on conditions
        if (needBraking) {
            train->setState(STATE_BRAKING);
            double braking = train->calculateBraking();
            double newSpeed = std::max(0.0, currentSpeed - braking * (_timeStepMinutes / 60.0));
            train->setCurrentSpeed(newSpeed);
        } else if (currentSpeed < speedLimit * 0.95) {
            train->setState(STATE_ACCELERATING);
            double accel = train->calculateAcceleration(speedLimit);
            double newSpeed = std::min(speedLimit, currentSpeed + accel * (_timeStepMinutes / 60.0));
            train->setCurrentSpeed(newSpeed);
        } else {
            train->setState(STATE_MAINTAINING);
            train->setCurrentSpeed(std::min(speedLimit, currentSpeed));
        }
        
        // Check if approaching end of rail (need to brake)
        double distanceRemaining = pos.currentRail->getLength() - pos.distanceOnRail;
        double stoppingDistance = (currentSpeed * currentSpeed) / (2.0 * train->calculateBraking() / 3.6);
        
        if (distanceRemaining < stoppingDistance && distanceRemaining < 5.0) {
            train->setState(STATE_BRAKING);
            double braking = train->calculateBraking();
            double newSpeed = std::max(0.0, currentSpeed - braking * (_timeStepMinutes / 60.0));
            train->setCurrentSpeed(newSpeed);
        }
        
        // Update position
        train->updatePosition(_timeStepMinutes);
    }
}

void SimulationManager::checkCollisions() {
    // Simple collision detection
    for (size_t i = 0; i < _trains.size(); ++i) {
        const Position& pos1 = _trains[i]->getPosition();
        if (pos1.currentRail == NULL) continue;
        
        for (size_t j = i + 1; j < _trains.size(); ++j) {
            const Position& pos2 = _trains[j]->getPosition();
            
            if (pos1.currentRail == pos2.currentRail) {
                double distance = std::abs(pos1.distanceOnRail - pos2.distanceOnRail);
                
                if (distance < 0.1) { // 100 meters
                    // Collision detected - stop both trains
                    _trains[i]->setState(STATE_STOPPED);
                    _trains[i]->setCurrentSpeed(0.0);
                    _trains[j]->setState(STATE_STOPPED);
                    _trains[j]->setCurrentSpeed(0.0);
                    
                    notify("COLLISION: " + _trains[i]->getName() + 
                           " and " + _trains[j]->getName());
                }
            }
        }
    }
}

void SimulationManager::handleTrainInteractions() {
    // Overtaking system - simplified
    // In real implementation, trains could switch tracks
}
