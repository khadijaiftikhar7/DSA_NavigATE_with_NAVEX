#include "Graph.h"
#include <iostream>

using std::cout;
using std::endl;

int Graph::idxCounter = 0;

Graph::Graph() {
    numberOfNodes = 0;
}

Graph::Graph(int n) {
    numberOfNodes = n;
}

void Graph::addNode(const std::string& name) {
    Node* n = new Node(idxCounter++, name, 0, 0);
    Nodes.push_back(n);
    neighboursList.push_back({});
    numberOfNodes++;
}

void Graph::addNode(const std::string& name, double x, double y) {
    Node* n = new Node(idxCounter++, name, (int)x, (int)y);
    Nodes.push_back(n);
    neighboursList.push_back({});
    numberOfNodes++;
}

void Graph::addNode(double x, double y) {
    Node* n = new Node(idxCounter++, "Unknown", (int)x, (int)y);
    Nodes.push_back(n);
    neighboursList.push_back({});
    numberOfNodes++;
}

int Graph::getIndex(const std::string& name) {
    for (int i = 0; i < (int)Nodes.size(); i++) {
        if (Nodes[i]->getLocationName() == name)
            return i;
    }
    return -1;
}

std::string Graph::getLocation(int index) const {
    if (index < 0 || index >= (int)Nodes.size()) return "Invalid";
    return Nodes[index]->getLocationName();
}

void Graph::addEdge(const std::string& sourceNode, const std::string& destinationNode, double weight) {
    int u = getIndex(sourceNode);
    int v = getIndex(destinationNode);

    if (u == -1 || v == -1) {
        cout << " Edge skipped: " << sourceNode << " -> " << destinationNode << endl;
        return;
    }

    neighboursList[u].push_back({ v, weight });
}

void Graph::removeEdge(const std::string& sourceNode, const std::string& destinationNode) {
    int u = getIndex(sourceNode);
    int v = getIndex(destinationNode);

    if (u == -1 || v == -1) return;

    auto& vec = neighboursList[u];
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (it->first == v) {
            vec.erase(it);
            break;
        }
    }
}

void Graph::removeEdgesOfNode(const std::string& locationName) {
    int idx = getIndex(locationName);
    if (idx == -1) return;

    neighboursList[idx].clear();

    for (auto& vec : neighboursList) {
        for (auto it = vec.begin(); it != vec.end();) {
            if (it->first == idx) it = vec.erase(it);
            else ++it;
        }
    }
}

void Graph::removeNode(const std::string& name) {
    int idx = getIndex(name);
    if (idx == -1) return;

    delete Nodes[idx];

    Nodes.erase(Nodes.begin() + idx);
    neighboursList.erase(neighboursList.begin() + idx);
    numberOfNodes--;

    for (auto& vec : neighboursList) {
        for (auto it = vec.begin(); it != vec.end();) {
            if (it->first == idx) it = vec.erase(it);
            else {
                if (it->first > idx) it->first--;
                ++it;
            }
        }
    }
}

int Graph::getNumberOfNodes() const {
    return numberOfNodes;
}
