//BLUEPRINT OF THE GRAPH CLASS. ONLY DEFINES THE ATTRIBUTES AND FUNCTIONS THAT WILL BE USED. IMPLEMENTATION WILL NOT BE PROVIDED HERE

//makes sure that when others include the template "Graph.h", it's only included once
#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <vector>
#include <utility>
#include <string>

class Graph {
    public:
    //total number of nodes in a graph
    int numberOfNodes;
    static int idxCounter;

    //stores all the nodes of the graph
    std::vector<Node*> Nodes;

    //std::pair<int, double> means there's an edge from a given node to its neighbouring node of value int with edge cost double
    //std::vector<std::pair<int, double>> is a vector that stores ALL the neighbouring nodes of a GIVEN node in (value, cost) pairs
    //std::vector<std::vector<std::pair<int, double>>> stores ALL neighbouring nodes of ALL nodes in a graph in form of edges
    std::vector<std::vector<std::pair<int, double>>> neighboursList;


    //CONSTRUCTORS
    //A constructor to initialize our graph with a specified number of nodes
    Graph(int numberOfNodes);

    //initializes an empty graph with NO nodes
    Graph();

    //METHODS
    //Creates and adds a node with given location to locationNames list. Creates empty vector for it in the neighboursList. Added node is not connected to the graph yet
    void addNode(const std::string& name);

    //Connects two nodes with an edge of cost = weight
    void addEdge(const std::string& sourceNode, const std::string& destinationNode, double weight);

    //removes a node from the graph, also removing any edges between it and its neighbours
    void removeNode(const std::string& name);

    //Only removes connection between two nodes, nodes remain as they are
    void removeEdge(std::string sourceNode, std::string destinationNode);

    //removes all edges connected to a given node (whether source or destianation)
    void removeEdgesOfNode(const std::string& locationName);
    
    //return index of a node with the given location name
    int getIndex(const std::string& name);

    //return name of location/place of a node with the given index
    std::string getLocation(int index);

    int getNumberOfNodes();

};

#endif
