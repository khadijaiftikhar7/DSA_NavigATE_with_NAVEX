#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include "Node.h"

using namespace std;

class Graph {
public:
    int numberOfNodes;
    static int idxCounter;

    vector<Node*> Nodes;
    vector<vector<pair<int, double>>> neighboursList;

    Graph();
    Graph(int numberOfNodes);

    void addNode(const string& name);
    void addNode(const string& name, double x, double y);
    void addNode(double x, double y);

    void addEdge(const string& sourceNode, const string& destinationNode, double weight);

    void removeNode(const string& name);
    void removeEdge(const string& sourceNode, const string& destinationNode);
    void removeEdgesOfNode(const string& locationName);

    int getIndex(const string& name);
    string getLocation(int index) const;  // Add const

    int getNumberOfNodes() const;   //  CONST FIX
};

#endif
