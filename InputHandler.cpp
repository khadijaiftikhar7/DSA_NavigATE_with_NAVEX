#include "InputHandler.h"
#include <iostream>

InputHandler::InputHandler(Graph* g) : graph(g) {}

bool InputHandler::isValidName(const std::string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (!isalnum(c) && c != '_') return false;
    }
    return true;
}

bool InputHandler::isValidWeight(double weight) {
    return weight > 0;
}

void InputHandler::handleAddNode() {
    std::string nodeName;
    std::cout << "Enter node name: ";
    std::cin >> nodeName;

    if (!isValidName(nodeName)) {
        std::cout << "Invalid node name.\n";
        return;
    }

    graph->addNode(nodeName);
    std::cout << "Node '" << nodeName << "' added.\n";
}

void InputHandler::handleAddEdge() {
    std::string sourceNode, destinationNode;
    double weight;

    std::cout << "Enter source node: ";
    std::cin >> sourceNode;
    std::cout << "Enter destination node: ";
    std::cin >> destinationNode;
    std::cout << "Enter edge weight: ";
    std::cin >> weight;

    if (!isValidName(sourceNode) || !isValidName(destinationNode)) {
        std::cout << "Invalid node name(s).\n";
        return;
    }

    if (!isValidWeight(weight)) {
        std::cout << "Weight must be positive.\n";
        return;
    }

    graph->addEdge(sourceNode, destinationNode, weight);
    std::cout << "Edge added.\n";
}

void InputHandler::handleRemoveNode() {
    std::string nodeName;
    std::cout << "Enter node name to remove: ";
    std::cin >> nodeName;

    if (!isValidName(nodeName)) {
        std::cout << "Invalid node name.\n";
        return;
    }

    graph->removeNode(nodeName);
    std::cout << "Node removed if it existed.\n";
}

void InputHandler::handleRemoveEdge() {
    std::string sourceNode, destinationNode;

    std::cout << "Enter source node: ";
    std::cin >> sourceNode;
    std::cout << "Enter destination node: ";
    std::cin >> destinationNode;

    if (!isValidName(sourceNode) || !isValidName(destinationNode)) {
        std::cout << "Invalid node name(s).\n";
        return;
    }

    graph->removeEdge(sourceNode, destinationNode);
    std::cout << "Edge removed if it existed.\n";
}

void InputHandler::displayNodes() {
    std::cout << "Nodes in the graph:\n";
    for (Node* n : graph->Nodes) {
        std::cout << "- " << n->getLocationName() << "\n";
    }
}

void InputHandler::displayNeighbours() {
    std::string nodeName;
    std::cout << "Enter node name: ";
    std::cin >> nodeName;

    if (!isValidName(nodeName)) {
        std::cout << "Invalid name.\n";
        return;
    }

    int idx = graph->getIndex(nodeName);
    if (idx == -1) {
        std::cout << "Node not found.\n";
        return;
    }

    std::cout << "Neighbours of '" << nodeName << "':\n";
    for (auto& pr : graph->neighboursList[idx]) {
        int neighbourIndex = pr.first;
        double cost = pr.second;
        std::cout << "- " << graph->getLocation(neighbourIndex)
                  << " (weight: " << cost << ")\n";
    }
}

void InputHandler::startMenu() {
    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Node\n";
        std::cout << "2. Add Edge\n";
        std::cout << "3. Remove Node\n";
        std::cout << "4. Remove Edge\n";
        std::cout << "5. Display Nodes\n";
        std::cout << "6. Display Neighbours\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                handleAddNode();
                break;
            case 2:
                handleAddEdge();
                break;
            case 3:
                handleRemoveNode();
                break;
            case 4:
                handleRemoveEdge();
                break;
            case 5:
                displayNodes();
                break;
            case 6:
                displayNeighbours();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}