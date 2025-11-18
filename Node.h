//BLUEPRINT OF THE NODE CLASS. ONLY DEFINES THE ATTRIBUTES AND FUNCTIONS THAT WILL BE USED. IMPLEMENTATION WILL NOT BE PROVIDED HERE

//makes sure that when others include the template "Node.h", it's only included once
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <utility>
#include <string>

class Node {
    private:
    //position of the node in the vector list
    int index; 
    //name of the location/place the node represents
    std::string name;
    //distance from the source node, used in pathfinding algorithms
    double distanceFromSource;
    //pointer to the previous node in the path, used in pathfinding algorithms
    Node *previousNode;
    //indicates whether the node has been visited, used in pathfinding algorithms
    bool visited;

    public:
    //CONSTRUCTORS
    Node(int index, const std::string& name);
    Node(int index);

    //METHODS
    //getters and setters
    int getIndex();
    std::string getLocationName();
    double getDistanceFromSource();
    Node *getPreviousNode();
    bool isVisited();
    void setLocationName(const std::string& name);
    void setVisited(bool status);
    void setPreviousNode(Node* prev);
    void setDistanceFromSource(double distance);


};

#endif
