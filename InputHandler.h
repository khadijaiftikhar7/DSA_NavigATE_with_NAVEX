//BLUEPRINT OF THE INPUT HANDLER CLASS. ONLY DEFINES THE FUNCTIONS USED FOR TAKING AND VALIDATING USER INPUT. IMPLEMENTATION WILL NOT BE PROVIDED HERE.

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Graph.h"
#include <string>
#include <vector>

class InputHandler {

    private:

    //pointer to the graph object this handler will work on
    Graph* graph;

    //validates that a node name is not empty and contains valid characters
    bool isValidName(const std::string& name);

    //validates that a weight is a positive number
    bool isValidWeight(double weight);

    
public:

    //CONSTRUCTORS
    //creates an InputHandler that works with a given graph
    InputHandler(Graph* graph);

    //METHODS

    //handles input for adding a node (asks user for name, validates it, then calls graph.addNode)
    void handleAddNode();

    //handles input for adding an edge (asks for both node names + weight and also validates them)
    void handleAddEdge();

    //handles input for removing a node
    void handleRemoveNode();

    //handles input for removing just an edge (not nodes)
    void handleRemoveEdge();

    //handles input for showing all nodes or edges in the graph
    void displayNodes();
    void displayNeighbours();

    //handles a main menu loop, repeatedly asking the user for what function they want to perform and then calling the relevant handler function
    void startMenu();

};

#endif
