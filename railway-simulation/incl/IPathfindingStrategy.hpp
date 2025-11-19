#ifndef IPATHFINDINGSTRATEGY_HPP
#define IPATHFINDINGSTRATEGY_HPP

#include <vector>
#include "Node.hpp"

/**
 * @interface IPathfindingStrategy
 * @brief Strategy Pattern - Interface for pathfinding algorithms
 * 
 * Allows different pathfinding algorithms to be used interchangeably.
 * SOLID Principle: Open/Closed Principle - open for extension, closed for modification
 */
class IPathfindingStrategy {
public:
    virtual ~IPathfindingStrategy() {}
    
    /**
     * @brief Find optimal path between two nodes
     * @param start Starting node
     * @param end Destination node
     * @return Vector of nodes representing the path
     */
    virtual std::vector<Node*> findPath(Node* start, Node* end) = 0;
};

#endif // IPATHFINDINGSTRATEGY_HPP
