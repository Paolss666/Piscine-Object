#include "../incl/DijkstraPathfinding.hpp"
#include "../incl/Rail.hpp"
#include <map>
#include <set>
#include <vector>
#include <limits>
#include <algorithm>

DijkstraPathfinding::DijkstraPathfinding() {
}

DijkstraPathfinding::~DijkstraPathfinding() {
}

double DijkstraPathfinding::calculateCost(Rail* rail) const {
    if (rail == NULL) {
        return std::numeric_limits<double>::max();
    }
    
    // Cost based on time = distance / speed
    // Lower speed = higher cost (takes longer)
    double distance = rail->getLength();
    double speed = rail->getSpeedLimit();
    
    if (speed <= 0) {
        return std::numeric_limits<double>::max();
    }
    
    return distance / speed; // Time-based cost
}

std::vector<Node*> DijkstraPathfinding::findPath(Node* start, Node* end) {
    std::vector<Node*> path;
    
    if (start == NULL || end == NULL) {
        return path;
    }
    
    if (start == end) {
        path.push_back(start);
        return path;
    }
    
    // Dijkstra's algorithm
    std::map<Node*, double> distances;
    std::map<Node*, Node*> previous;
    std::set<Node*> unvisited;
    
    // Initialize
    distances[start] = 0.0;
    unvisited.insert(start);
    
    while (!unvisited.empty()) {
        // Find node with minimum distance
        Node* current = NULL;
        double minDist = std::numeric_limits<double>::max();
        
        for (std::set<Node*>::iterator it = unvisited.begin(); 
             it != unvisited.end(); ++it) {
            double dist = (distances.find(*it) != distances.end()) 
                         ? distances[*it] 
                         : std::numeric_limits<double>::max();
            if (dist < minDist) {
                minDist = dist;
                current = *it;
            }
        }
        
        if (current == NULL || minDist == std::numeric_limits<double>::max()) {
            break; // No path found
        }
        
        if (current == end) {
            break; // Found destination
        }
        
        unvisited.erase(current);
        
        // Check neighbors
        const std::vector<Rail*>& rails = current->getConnectedRails();
        for (size_t i = 0; i < rails.size(); ++i) {
            Node* neighbor = rails[i]->getOtherNode(current);
            if (neighbor == NULL) {
                continue;
            }
            
            double edgeCost = calculateCost(rails[i]);
            double currentDist = distances[current];
            double newDist = currentDist + edgeCost;
            
            double neighborDist = (distances.find(neighbor) != distances.end())
                                 ? distances[neighbor]
                                 : std::numeric_limits<double>::max();
            
            if (newDist < neighborDist) {
                distances[neighbor] = newDist;
                previous[neighbor] = current;
                unvisited.insert(neighbor);
            }
        }
    }
    
    // Reconstruct path
    if (previous.find(end) == previous.end() && start != end) {
        return path; // No path found
    }
    
    Node* current = end;
    while (current != NULL) {
        path.insert(path.begin(), current);
        if (current == start) {
            break;
        }
        current = (previous.find(current) != previous.end()) 
                 ? previous[current] 
                 : NULL;
    }
    
    return path;
}
