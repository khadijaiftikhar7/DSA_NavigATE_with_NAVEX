#include "Node.h"

Node::Node(int index, const std::string& name) {
    this->index = index;
    this->name = name;
    distanceFromSource = 0.0;
    previousNode = nullptr;
    visited = false;
    x = y = 0;
}  

Node::Node(int index) {
    this->index = index;
    this->name = "Unknown";
    distanceFromSource = 0.0;
    previousNode = nullptr;
    visited = false;
    x = y = 0;
}

Node::Node(int index, const std::string& name, int x, int y) {
    this->index = index;
    this->name = name;
    distanceFromSource = 0.0;
    previousNode = nullptr;
    visited = false;
    this->x = x;
    this->y = y;
}

int Node::getIndex() {
    return index;
}

std::string Node::getLocationName() {
    return name;
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
    this->name = name;
}

void Node::setVisited(bool visitStatus) {
    visited = visitStatus;
}

void Node::setPreviousNode(Node* prev) {
    previousNode = prev;
}

void Node::setDistanceFromSource(double distance) {
    distanceFromSource = distance;
}

int Node::getX() {
    return x;
}

int Node::getY() {
    return y;
}

void Node::setX(int x) {
    this->x = x;
}

void Node::setY(int y) {
    this->y = y;
}

