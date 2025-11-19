#include "../incl/Train.hpp"
#include <cmath>
#include <algorithm>

int Train::_nextId = 1;

Train::Train(const std::string& name, double weight, double friction,
             double maxAccel, double maxBrake, Node* dep, Node* dest,
             const Time& depTime, const Time& stopDur)
    : _id(_nextId++), _name(name), _weight(weight), _frictionCoeff(friction),
      _maxAccelForce(maxAccel), _maxBrakeForce(maxBrake),
      _departure(dep), _destination(dest), _departureTime(depTime),
      _stopDuration(stopDur), _state(STATE_STOPPED), _currentSpeed(0.0),
      _currentPathIndex(0), _currentTime(depTime), _totalDistanceToGo(0.0) {
}

Train::~Train() {
}

void Train::setPath(const std::vector<Node*>& path) {
    _path = path;
    _currentPathIndex = 0;
    updateTotalDistance();
    
    // Initialize position
    if (_path.size() >= 2) {
        _position.lastNode = _path[0];
        _position.nextNode = _path[1];
        _position.currentRail = _position.lastNode->getRailTo(_position.nextNode);
        _position.distanceOnRail = 0.0;
    }
}

void Train::updateTotalDistance() {
    _totalDistanceToGo = 0.0;
    
    for (size_t i = _currentPathIndex; i < _path.size() - 1; ++i) {
        Rail* rail = _path[i]->getRailTo(_path[i + 1]);
        if (rail != NULL) {
            if (i == _currentPathIndex) {
                // Subtract already traveled distance on current rail
                _totalDistanceToGo += rail->getLength() - _position.distanceOnRail;
            } else {
                _totalDistanceToGo += rail->getLength();
            }
        }
    }
}

double Train::calculateAcceleration(double speedLimit) const {
    // F = ma => a = F/m
    // Account for friction: F_net = F_accel - F_friction
    // F_friction = μ * m * g (where g ≈ 9.81 m/s²)
    
    const double g = 9.81; // m/s²
    double frictionForce = _frictionCoeff * _weight * 1000.0 * g / 1000.0; // Convert to kN
    double netForce = _maxAccelForce - frictionForce;
    
    if (netForce <= 0) {
        return 0.0;
    }
    if (_currentSpeed >= speedLimit) {
        return 0.0;
    }
    
    // a = F/m (m in metric tons, F in kN)
    double accel = netForce / _weight; // km/h per second approximately
    return accel * 3.6; // Convert to km/h²
}

double Train::calculateBraking() const {
    // Braking deceleration
    double decel = _maxBrakeForce / _weight;
    return decel * 3.6; // Convert to km/h²
}

void Train::updatePosition(double timeStepMinutes) {
    if (_state == STATE_STOPPED || _position.currentRail == NULL) {
        return;
    }
    
    // Convert time to hours
    double timeStepHours = timeStepMinutes / 60.0;
    
    // Calculate distance traveled
    double distance = _currentSpeed * timeStepHours;
    
    _position.distanceOnRail += distance;
    
    // Check if we've reached the end of current rail
    if (_position.distanceOnRail >= _position.currentRail->getLength()) {
        _position.distanceOnRail = _position.currentRail->getLength();
        
        // Move to next rail segment
        _currentPathIndex++;
        
        if (_currentPathIndex >= _path.size() - 1) {
            // Arrived at destination
            _state = STATE_STOPPED;
            _currentSpeed = 0.0;
        } else {
            // Continue to next segment
            _position.lastNode = _path[_currentPathIndex];
            _position.nextNode = _path[_currentPathIndex + 1];
            
            Rail* prevRail = _position.currentRail;
            _position.currentRail = _position.lastNode->getRailTo(_position.nextNode);
            
            if (prevRail != NULL) {
                prevRail->removeTrain(this);
            }
            if (_position.currentRail != NULL) {
                _position.currentRail->addTrain(this);
            }
            
            _position.distanceOnRail = 0.0;
        }
    }
    
    updateTotalDistance();
}

bool Train::hasArrived() const {
    return (_currentPathIndex >= _path.size() - 1 && 
            _state == STATE_STOPPED);
}

std::string Train::getStateString() const {
    switch (_state) {
        case STATE_STOPPED: return "Stopped";
        case STATE_ACCELERATING: return "Speed up";
        case STATE_MAINTAINING: return "Maintain";
        case STATE_BRAKING: return "Braking";
        case STATE_WAITING: return "Waiting";
        default: return "Unknown";
    }
}
