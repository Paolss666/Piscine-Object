#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "Node.hpp"
#include "Rail.hpp"
#include "Types.hpp"

#include <string>
#include <vector>

/**
 * @class Train
 * @brief Represents a train with physical properties and state
 * 
 * Encapsulates train characteristics, current state, and path.
 * Implements physics-based movement simulation.
 */
class Train {
private:
    static int _nextId;
    
    int _id;
    std::string _name;
    double _weight;              // metric tons
    double _frictionCoeff;
    double _maxAccelForce;       // kN
    double _maxBrakeForce;       // kN
    Node* _departure;
    Node* _destination;
    Time _departureTime;
    Time _stopDuration;
    
    // Runtime state
    TrainState _state;
    double _currentSpeed;        // km/h
    Position _position;
    std::vector<Node*> _path;
    size_t _currentPathIndex;
    Time _currentTime;
    double _totalDistanceToGo;
    
public:
    // Constructor
    Train(const std::string& name, double weight, double friction,
          double maxAccel, double maxBrake, Node* dep, Node* dest,
          const Time& depTime, const Time& stopDur);
    
    // Destructor
    ~Train();
    
    // Getters
    int getId() const { return _id; }
    const std::string& getName() const { return _name; }
    double getWeight() const { return _weight; }
    double getFrictionCoeff() const { return _frictionCoeff; }
    double getMaxAccelForce() const { return _maxAccelForce; }
    double getMaxBrakeForce() const { return _maxBrakeForce; }
    Node* getDeparture() const { return _departure; }
    Node* getDestination() const { return _destination; }
    const Time& getDepartureTime() const { return _departureTime; }
    const Time& getStopDuration() const { return _stopDuration; }
    TrainState getState() const { return _state; }
    double getCurrentSpeed() const { return _currentSpeed; }
    const Position& getPosition() const { return _position; }
    const std::vector<Node*>& getPath() const { return _path; }
    const Time& getCurrentTime() const { return _currentTime; }
    double getTotalDistanceToGo() const { return _totalDistanceToGo; }
    
    // Setters
    void setState(TrainState state) { _state = state; }
    void setCurrentSpeed(double speed) { _currentSpeed = speed; }
    void setPath(const std::vector<Node*>& path);
    void setCurrentTime(const Time& time) { _currentTime = time; }
    
    // Methods
    void updatePosition(double timeStepMinutes);
    double calculateAcceleration(double speedLimit) const;
    double calculateBraking() const;
    bool hasArrived() const;
    void updateTotalDistance();
    std::string getStateString() const;
};

#endif // TRAIN_HPP
