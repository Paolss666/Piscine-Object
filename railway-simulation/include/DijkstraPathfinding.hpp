#ifndef DIJKSTRAPATHFINDING_HPP
#define DIJKSTRAPATHFINDING_HPP

#include "IPathfindingStrategy.hpp"
#include <map>

/**
 * @class DijkstraPathfinding
 * @brief Concrete implementation of pathfinding using Dijkstra's algorithm
 * 
 * Finds shortest path considering both distance and speed limits.
 */
class DijkstraPathfinding : public IPathfindingStrategy {
public:
    DijkstraPathfinding();
    virtual ~DijkstraPathfinding();
    
    virtual std::vector<Node*> findPath(Node* start, Node* end);
    
private:
    double calculateCost(Rail* rail) const;
};

#endif // DIJKSTRAPATHFINDING_HPP
