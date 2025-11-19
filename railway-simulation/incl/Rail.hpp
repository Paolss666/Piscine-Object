#ifndef RAIL_HPP
#define RAIL_HPP

#include "Node.hpp"
#include "Types.hpp"
#include <vector>
#include "Train.hpp"  

/**
 * 
 * Encapsulates rail properties including length, speed limit,
 * and connected nodes. Manages train occupation.
 */
class Train; // Forward declaration
class Rail {
private:
    Node* _startNode;
    Node* _endNode;
    double _length;        // km
    double _speedLimit;    // km/h
    std::vector<Train*> _occupyingTrains;

public:
    // Constructor
    Rail(Node* start, Node* end, double length, double speedLimit);
    
    // Destructor
    ~Rail();
    
    // Getters
    Node* getStartNode() const { return _startNode; }
    Node* getEndNode() const { return _endNode; }
    double getLength() const { return _length; }
    double getSpeedLimit() const { return _speedLimit; }
    const std::vector<Train*>& getOccupyingTrains() const { return _occupyingTrains; }
    
    // Methods
    Node* getOtherNode(Node* node) const;
    void addTrain(Train* train);
    void removeTrain(Train* train);
    bool isOccupied() const;
    Train* getTrainAhead(Train* train, double position) const;
};

#endif // RAIL_HPP
