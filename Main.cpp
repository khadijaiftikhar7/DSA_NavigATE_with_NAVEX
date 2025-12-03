#include "Graph.h"
#include "InputHandler.h"
#include "Updater.h"
#include "GraphLoader.h"
#include "WeatherManager.h"
#include <iostream>

int main() {
    // Create graph
    Graph* g = new Graph();
    
    // Load nodes and edges from files
    GraphLoader::loadNodes(g, "IslamabadNodes.txt");
    GraphLoader::loadEdges(g, "IslamabadEdges.txt");
    
    std::cout << "Graph loaded successfully!\n";
    std::cout << "Total nodes: " << g->getNumberOfNodes() << "\n";
    
    // Create weather manager with your API key
    WeatherManager wm("e9b7b1f6b6d92567ef5dba75682be028"); // Replace with actual key
    
    // Create input handler and updater
    InputHandler ih(g);
    Updater up(g, &wm);
    
    // Main menu
    int choice;
    do {
        std::cout << "\n========== ISLAMABAD NAVIGATION SYSTEM ==========\n";
        std::cout << "1. Graph Operations Menu (Add/Remove Nodes/Edges)\n";
        std::cout << "2. Live Updates Menu (Weather/Routes/Blockages)\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                ih.startMenu();
                break;
            case 2:
                up.updateMenu();
                break;
            case 0:
                std::cout << "Exiting... Thank you!\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    
    // Cleanup
    delete g;
    
    return 0;
}