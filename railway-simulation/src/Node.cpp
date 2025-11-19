#include "../incl/Node.hpp"
#include "../incl/Rail.hpp"

Node::Node(const std::string& name) 
    : _name(name), _isCity(false) {
    determineIfCity();
}

Node::~Node() {
    // Rails are managed by RailwayNetwork
}

void Node::addRail(Rail* rail) {
    if (rail != NULL) {
        _connectedRails.push_back(rail);
    }
}

Rail* Node::getRailTo(Node* destination) const {
    for (size_t i = 0; i < _connectedRails.size(); ++i) {
        if (_connectedRails[i]->getOtherNode(const_cast<Node*>(this)) == destination) {
            return _connectedRails[i];
        }
    }
    return NULL;
}

void Node::determineIfCity() {
    // Cities typically start with "City"
    _isCity = (_name.find("City") == 0);
}
