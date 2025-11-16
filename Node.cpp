#include "Node.h"

Node::Node(int index, std::string locationName) {
    this->index = index;
    this->locationName = locationName;
    distanceFromSource = 0.0;
    previousNode = nullptr;
    visited = false;
}  

Node::Node(int index) {
    this->index = index;
    this->locationName = "Unknown";
    distanceFromSource = 0.0;
    previousNode = nullptr;
    visited = false;
}

int Node::getIndex() {
    return index;
}

std::string Node::getLocationName() {
    return locationName;
}

double Node::getDistanceFromSource() {
    return distanceFromSource;
}

Node* Node::getPreviousNode() {
    return previousNode;
}

bool Node::isVisited() {
    return visited;
}

void Node::setLocationName(const std::string& name) {
    locationName = name;
}

void Node::setVisited(bool visitStatus) {
    visited = visitStatus;
}