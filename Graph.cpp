#include "Graph.h"

int Graph::idxCounter = 0;

Graph::Graph(int numberOfNodes){
    this->numberOfNodes = numberOfNodes;
    Nodes.resize(numberOfNodes); //Resizes the nodes vector list to hold the specified number of nodes
    neighboursList.resize(numberOfNodes); //Resizes the adjacency list to hold the specified number of nodes
}

Graph::Graph(){
    this->numberOfNodes = 0;
}

void Graph::addNode(const std::string& locationName){
    Nodes.push_back(new Node(idxCounter, locationName));
    //Creates a node with auto incremented index and given location name
  //Adds the new node to the nodes list
    idxCounter++; //Increments the index counter for the next node
    numberOfNodes++; //Increments the total number of nodes in the graph
}

void Graph::addNode(const std::string& locationName, int x, int y){
    Nodes.push_back(new Node(idxCounter, locationName, x, y));
    //Creates a node with auto incremented index, given location name and coordinates
  //Adds the new node to the nodes list
    idxCounter++; //Increments the index counter for the next node
    numberOfNodes++; //Increments the total number of nodes in the graph
}

void Graph::addNode(int x, int y){
    Nodes.push_back(new Node(idxCounter));
    //Creates a node with auto incremented index and default location name "Unknown" and given coordinates
  //Adds the new node to the nodes list
    idxCounter++; //Increments the index counter for the next node
    numberOfNodes++; //Increments the total number of nodes in the graph
}

void Graph::addEdge(const std::string& sourceLocation, const std::string& destinationLocation, double weight){
    int sourceIndex = getIndex(sourceLocation); //gets index of the source location
    int destinationIndex = getIndex(destinationLocation); //gets index of destination location
    if(sourceIndex != -1 && destinationIndex != -1){
        neighboursList[sourceIndex].push_back({destinationIndex, weight}); //Adds the edge to the correct source node in the adjacency list
    }
 
}

void Graph::removeEdge(std::string sourceNode, std::string destinationNode) {
    int sourceIndex = getIndex(sourceNode); //get index of source node
    int destinationIndex = getIndex(destinationNode); //get index of destination node

    if (sourceIndex == -1 || destinationIndex == -1) {
        return; //one of the nodes doesn't exist
    }

    // go through all edges of the source node to see which edge has given destination node
    for (int i = 0; i < neighboursList[sourceIndex].size(); i++) {
        if (neighboursList[sourceIndex][i].first == destinationIndex) {
            neighboursList[sourceIndex].erase(neighboursList[sourceIndex].begin() + i);
            break; 
        }
    }
}

void Graph::removeEdgesOfNode(const std::string& locationName) {
    int nodeIndex = getIndex(locationName);

    if (nodeIndex == -1) {
        return; 
    }

    //removes edges in which given node is source node
    neighboursList[nodeIndex].clear();

    //removes all edges in which given node is destination node
    for (int i = 0; i < neighboursList.size(); i++) {
        for (int j = 0; j < neighboursList[i].size(); j++) {
            if (neighboursList[i][j].first == nodeIndex) {
                neighboursList[i].erase(neighboursList[i].begin() + j);
                j--; 
            }
        }
    }
}

void Graph::removeNode(const std::string& locationName) {
    int nodeIndex = getIndex(locationName); //find index of given node

    if (nodeIndex == -1) {
        return; 
    }

    //remove edges in which given niode is invloved
    removeEdgesOfNode(locationName);

    //remove node from nodes list
    Nodes.erase(Nodes.begin() + nodeIndex);

    //remove node's entry from neighbours list
    neighboursList.erase(neighboursList.begin() + nodeIndex);

    //update indices in neighbours list
    for (int i = 0; i < neighboursList.size(); i++) {
        for (int j = 0; j < neighboursList[i].size(); j++) {
            if (neighboursList[i][j].first > nodeIndex) {
                neighboursList[i][j].first--; 
            }
        }
    }

    numberOfNodes--; 
}

int Graph::getIndex(const std::string& locationName) {
    for (int i = 0; i < Nodes.size(); i++) {
        if (Nodes[i]->getLocationName() == locationName) {
            return Nodes[i]->getIndex();
        }
    }
    return -1; 
}

std::string Graph::getLocation(int index) {
    if (index >= 0 && index < Nodes.size()) {
        return Nodes[index]->getLocationName();
    }
    return "index out of bounds"; 
}

int Graph::getNumberOfNodes() {
    return numberOfNodes;
}
