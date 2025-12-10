#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <utility>
#include "Node.h"

class Graph {
public:
    int numberOfNodes;
    static int idxCounter;

    std::vector<Node*> Nodes;
    std::vector<std::vector<std::pair<int, double>>> neighboursList;

    Graph();
    Graph(int numberOfNodes);

    void addNode(const std::string& name);
    void addNode(const std::string& name, double x, double y);
    void addNode(double x, double y);

    void addEdge(const std::string& sourceNode, const std::string& destinationNode, double weight);

    void removeNode(const std::string& name);
    void removeEdge(const std::string& sourceNode, const std::string& destinationNode);
    void removeEdgesOfNode(const std::string& locationName);

    int getIndex(const std::string& name);
    std::string getLocation(int index) const;

    int getNumberOfNodes() const;
};

#endif // GRAPH_H
