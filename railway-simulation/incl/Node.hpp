#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>
#include "Types.hpp"

class Rail;

/**
 * @class Node
 * @brief Represents a node (station or junction) in the railway network
 * 
 * Encapsulates node information and connected rails.
 * Implements proper encapsulation with getters/setters.
 */
class Node {
private:
    std::string _name;
    std::vector<Rail*> _connectedRails;
    bool _isCity;

public:
    // Constructor
    explicit Node(const std::string& name);
    
    // Destructor
    ~Node();
    
    // Getters
    const std::string& getName() const { return _name; }
    const std::vector<Rail*>& getConnectedRails() const { return _connectedRails; }
    bool isCity() const { return _isCity; }
    
    // Methods
    void addRail(Rail* rail);
    Rail* getRailTo(Node* destination) const;
    
    // Utility
    void determineIfCity();
};

#endif // NODE_HPP
