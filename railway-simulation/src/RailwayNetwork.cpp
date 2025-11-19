#include "../incl/RailwayNetwork.hpp"

RailwayNetwork::RailwayNetwork() {
}

RailwayNetwork::~RailwayNetwork() {
    clear();
}

Node* RailwayNetwork::addNode(const std::string& name) {
    if (_nodes.find(name) != _nodes.end()) {
        return _nodes[name]; // Already exists
    }
    
    Node* node = new Node(name);
    _nodes[name] = node;
    return node;
}

Node* RailwayNetwork::getNode(const std::string& name) const {
    std::map<std::string, Node*>::const_iterator it = _nodes.find(name);
    if (it != _nodes.end()) {
        return it->second;
    }
    return NULL;
}

bool RailwayNetwork::hasNode(const std::string& name) const {
    return _nodes.find(name) != _nodes.end();
}

Rail* RailwayNetwork::addRail(const std::string& startName, 
                               const std::string& endName,
                               double length, double speedLimit) {
    Node* start = getNode(startName);
    Node* end = getNode(endName);
    
    if (start == NULL || end == NULL) {
        return NULL;
    }
    
    Rail* rail = new Rail(start, end, length, speedLimit);
    _rails.push_back(rail);
    return rail;
}

void RailwayNetwork::clear() {
    // Delete all rails
    for (size_t i = 0; i < _rails.size(); ++i) {
        delete _rails[i];
    }
    _rails.clear();
    
    // Delete all nodes
    for (std::map<std::string, Node*>::iterator it = _nodes.begin();
         it != _nodes.end(); ++it) {
        delete it->second;
    }
    _nodes.clear();
}
