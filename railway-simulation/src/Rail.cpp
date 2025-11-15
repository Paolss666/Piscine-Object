#include "../include/Rail.hpp"
#include "../include/Train.hpp"
#include <algorithm>

Rail::Rail(Node* start, Node* end, double length, double speedLimit)
    : _startNode(start), _endNode(end), _length(length), _speedLimit(speedLimit) {
    
    if (start != NULL) {
        start->addRail(this);
    }
    if (end != NULL) {
        end->addRail(this);
    }
}

Rail::~Rail() {
    // Trains are managed by SimulationManager
}

Node* Rail::getOtherNode(Node* node) const {
    if (node == _startNode) {
        return _endNode;
    } else if (node == _endNode) {
        return _startNode;
    }
    return NULL;
}

void Rail::addTrain(Train* train) {
    if (train != NULL) {
        _occupyingTrains.push_back(train);
    }
}

void Rail::removeTrain(Train* train) {
    std::vector<Train*>::iterator it = std::find(_occupyingTrains.begin(), 
                                                   _occupyingTrains.end(), 
                                                   train);
    if (it != _occupyingTrains.end()) {
        _occupyingTrains.erase(it);
    }
}

bool Rail::isOccupied() const {
    return !_occupyingTrains.empty();
}

Train* Rail::getTrainAhead(Train* train, double position) const {
    // Find closest train ahead on this rail
    Train* closestTrain = NULL;
    double minDistance = _length;
    
    for (size_t i = 0; i < _occupyingTrains.size(); ++i) {
        if (_occupyingTrains[i] != train) {
            const Position& otherPos = _occupyingTrains[i]->getPosition();
            if (otherPos.currentRail == this) {
                double distance = otherPos.distanceOnRail - position;
                if (distance > 0 && distance < minDistance) {
                    minDistance = distance;
                    closestTrain = _occupyingTrains[i];
                }
            }
        }
    }
    
    return closestTrain;
}
