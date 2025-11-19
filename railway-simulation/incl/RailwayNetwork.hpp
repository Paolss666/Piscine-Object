#ifndef RAILWAYNETWORK_HPP
#define RAILWAYNETWORK_HPP

#include "Node.hpp"
#include "Rail.hpp"
#include "Types.hpp"
#include <map>
#include <string>
#include <vector>

/**
 * @class RailwayNetwork
 * @brief Manages the railway network graph
 * 
 * Encapsulates network structure and provides access to nodes and rails.
 * SOLID: Single Responsibility - manages network structure only
 */
class RailwayNetwork {
private:
    std::map<std::string, Node*> _nodes;
    std::vector<Rail*> _rails;

public:
    RailwayNetwork();
    ~RailwayNetwork();
    
    // Node management
    Node* addNode(const std::string& name);
    Node* getNode(const std::string& name) const;
    bool hasNode(const std::string& name) const;
    
    // Rail management
    Rail* addRail(const std::string& startName, const std::string& endName,
                  double length, double speedLimit);
    const std::vector<Rail*>& getRails() const { return _rails; }
    
    // Utility
    void clear();
    size_t getNodeCount() const { return _nodes.size(); }
    size_t getRailCount() const { return _rails.size(); }
};

#endif // RAILWAYNETWORK_HPP
