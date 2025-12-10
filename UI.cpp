#define _HAS_STD_BYTE 0

#include <windows.h>
#include "UI.h"
#include "PathFinder.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ============== UTILITY FUNCTIONS ==============

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}

void printBorder() {
    setColor(11);
    cout << "============================================================\n";
    setColor(7);
}

void pauseScreen() {
    cout << "\n";
    setColor(14);
    cout << "=========================================\n";
    cout << "  Press ENTER to continue...\n";
    cout << "=========================================";
    setColor(7);
    cin.ignore(1000, '\n');
    cin.get();
}

void showHeader() {
    clearScreen();
    setColor(11);
    cout << "\n";
    cout << "============================================================\n";
    setColor(14);
    cout << "                                                            \n";
    cout << "           N   N   AAA   V     V  EEEEE  X   X             \n";
    cout << "           NN  N  A   A  V     V  E       X X              \n";
    cout << "           N N N  AAAAA   V   V   EEEE     X               \n";
    cout << "           N  NN  A   A    V V    E       X X              \n";
    cout << "           N   N  A   A     V     EEEEE  X   X             \n";
    cout << "                                                            \n";
    setColor(10);
    cout << "         Smart Navigation System for Islamabad             \n";
    setColor(11);
    cout << "                    Version 2.0                             \n";
    cout << "============================================================\n\n";
    setColor(7);
}

void showLoadingAnimation(const string& message) {
    setColor(14);
    cout << "\n  >> " << message;
    setColor(11);
    for (int i = 0; i < 5; i++) {
        Sleep(200);
        cout << "=";
        cout.flush();
    }
    setColor(10);
    cout << " DONE!\n";
    setColor(7);
}

// ============== FEATURE FUNCTIONS ==============

void displayGraphStructure(Graph* g) {
    showHeader();
    setColor(14);
    cout << "  GRAPH STRUCTURE\n";
    printBorder();
    setColor(7);

    int n = g->getNumberOfNodes();
    if (n == 0) {
        setColor(12);
        cout << "  WARNING: No nodes in the graph!\n";
        setColor(7);
        printBorder();
        pauseScreen();
        return;
    }

    for (int i = 0; i < n; i++) {
        setColor(14);
        cout << "  * " << left << setw(20) << g->getLocation(i);
        setColor(7);
        cout << " --> ";

        if (g->neighboursList[i].empty()) {
            setColor(8);
            cout << "[No connections]";
            setColor(7);
        } else {
            for (size_t j = 0; j < g->neighboursList[i].size(); j++) {
                int neighbor = g->neighboursList[i][j].first;
                double weight = g->neighboursList[i][j].second;

                setColor(11);
                cout << g->getLocation(neighbor);
                setColor(7);
                cout << " (" << fixed << setprecision(1) << weight << " km)";

                if (j < g->neighboursList[i].size() - 1) {
                    cout << ", ";
                }
            }
        }
        cout << "\n";
    }

    printBorder();
    pauseScreen();
}

void findShortestPath(Graph* g, RouteHistory* history) {
    showHeader();
    setColor(14);
    cout << "  FIND SHORTEST PATH (Dijkstra Algorithm)\n";
    printBorder();
    setColor(7);

    string from, to;
    cout << "\n  Enter Source Location: ";
    cin.ignore();
    getline(cin, from);

    cout << "  Enter Destination: ";
    getline(cin, to);

    int srcIdx = g->getIndex(from);
    int dstIdx = g->getIndex(to);

    if (srcIdx == -1) {
        setColor(12);
        cout << "\n  ERROR: Source location '" << from << "' not found!\n";
        setColor(7);
        printBorder();
        pauseScreen();
        return;
    }

    if (dstIdx == -1) {
        setColor(12);
        cout << "\n  ERROR: Destination '" << to << "' not found!\n";
        setColor(7);
        printBorder();
        pauseScreen();
        return;
    }

    showLoadingAnimation("Calculating shortest path");

    PathResult result = dijkstra(*g, srcIdx, dstIdx);

    if (!result.success || result.path.empty()) {
        setColor(12);
        cout << "\n  ERROR: No path found between " << from << " and " << to << "!\n";
        setColor(7);
        printBorder();
        pauseScreen();
        return;
    }

    history->addRoute(from, to);

    setColor(10);
    cout << "\n  SUCCESS: Path Found!\n\n";
    setColor(7);
    cout << "  Total Distance: ";
    setColor(14);
    cout << fixed << setprecision(2) << result.distance << " km\n\n";
    setColor(7);

    setColor(11);
    cout << "  Route:\n";
    setColor(7);
    cout << "  ";
    for (size_t i = 0; i < result.path.size(); i++) {
        setColor(14);
        cout << g->getLocation(result.path[i]);
        setColor(7);

        if (i < result.path.size() - 1) {
            setColor(10);
            cout << " ---> ";
            setColor(7);
        }
    }
    cout << "\n\n";

    printBorder();
    pauseScreen();
}

void findAStarPath(Graph* g, RouteHistory* history) {
    showHeader();
    setColor(14);
    cout << "  FIND OPTIMAL PATH (A* Algorithm)\n";
    printBorder();
    setColor(7);

    string from, to;
    cout << "\n  Enter Source Location: ";
    cin.ignore();
    getline(cin, from);

    cout << "  Enter Destination: ";
    getline(cin, to);

    int srcIdx = g->getIndex(from);
    int dstIdx = g->getIndex(to);

    if (srcIdx == -1 || dstIdx == -1) {
        setColor(12);
        cout << "\n  ERROR: Invalid source or destination!\n";
        setColor(7);
        printBorder();
        pauseScreen();
        return;
    }

    showLoadingAnimation("Calculating optimal path with A*");

    PathResult result = AStar(*g, srcIdx, dstIdx);

    if (!result.success || result.path.empty()) {
        setColor(12);
        cout << "\n  ERROR: No path found!\n";
        setColor(7);
        printBorder();
        pauseScreen();
        return;
    }

    history->addRoute(from, to);

    setColor(10);
    cout << "\n  SUCCESS: Optimal Path Found!\n\n";
    setColor(7);
    cout << "  Total Distance: ";
    setColor(14);
    cout << fixed << setprecision(2) << result.distance << " km\n\n";
    setColor(7);

    setColor(11);
    cout << "  Route:\n";
    setColor(7);
    cout << "  ";
    for (size_t i = 0; i < result.path.size(); i++) {
        setColor(14);
        cout << g->getLocation(result.path[i]);
        setColor(7);

        if (i < result.path.size() - 1) {
            setColor(10);
            cout << " ---> ";
            setColor(7);
        }
    }
    cout << "\n\n";

    printBorder();
    pauseScreen();
}

void showRouteHistory(RouteHistory* history) {
    showHeader();
    setColor(14);
    cout << "  ROUTE HISTORY\n";
    printBorder();
    setColor(7);

    history->showRecentRoutes();
    cout << "\n";
    history->showMostUsedRoute();

    printBorder();
    pauseScreen();
}

void loadGraphFromFile(Graph* g) {
    showHeader();
    setColor(14);
    cout << "  LOAD GRAPH FROM FILE\n";
    printBorder();
    setColor(7);

    string nodeFile, edgeFile;
    cout << "\n  Enter Nodes File Path: ";
    cin.ignore();
    getline(cin, nodeFile);

    cout << "  Enter Edges File Path: ";
    getline(cin, edgeFile);

    showLoadingAnimation("Loading graph data");

    GraphLoader::loadNodes(g, nodeFile);
    GraphLoader::loadEdges(g, edgeFile);

    setColor(10);
    cout << "\n  SUCCESS: Graph loaded successfully!\n";
    cout << "  Total Nodes: " << g->getNumberOfNodes() << "\n";
    setColor(7);

    printBorder();
    pauseScreen();
}

void demonstrateAlgorithm(Graph* g) {
    showHeader();
    setColor(14);
    cout << "  ALGORITHM DEMONSTRATION\n";
    printBorder();
    setColor(7);
    
    cout << "\n  This will show step-by-step how Dijkstra's algorithm\n";
    cout << "  finds the shortest path between two locations.\n\n";
    
    cout << "  Choose a demo:\n";
    cout << "  [1] F6 to BLUE (Short path)\n";
    cout << "  [2] F6 to BAHRIA (Long path)\n";
    cout << "  [3] Custom locations\n";
    cout << "  [0] Back\n\n";
    
    setColor(14);
    cout << "  >> Enter choice: ";
    setColor(7);
    
    int choice;
    cin >> choice;
    
    string from, to;
    
    switch(choice) {
        case 1:
            from = "F6";
            to = "BLUE";
            break;
        case 2:
            from = "F6";
            to = "BAHRIA";
            break;
        case 3:
            cout << "\n  Enter source: ";
            cin >> from;
            cout << "  Enter destination: ";
            cin >> to;
            break;
        case 0:
            return;
        default:
            cout << "\n  Invalid choice!\n";
            pauseScreen();
            return;
    }
    
    int srcIdx = g->getIndex(from);
    int dstIdx = g->getIndex(to);
    
    if (srcIdx == -1 || dstIdx == -1) {
        setColor(12);
        cout << "\n  ERROR: Invalid locations!\n";
        setColor(7);
        pauseScreen();
        return;
    }
    
    // Run visualization
    PathResult result = dijkstra(*g, srcIdx, dstIdx);
    
    if (result.success) {
        setColor(10);
        cout << "\n\n  Final Distance: " << fixed << setprecision(2) 
             << result.distance << " km\n";
        setColor(7);
    }
    
    pauseScreen();
}

// ============== MAIN UI LOOP ==============

void runUI(Graph* g, InputHandler* ih, Updater* up) {
    RouteHistory history;
    int choice;

    showHeader();
    setColor(10);
    cout << "  Welcome! Islamabad map data loaded successfully.\n";
    cout << "  Total locations: " << g->getNumberOfNodes() << "\n";
    setColor(7);
    Sleep(2000);

    do {
        showHeader();

        setColor(14);
        cout << "  MAIN MENU\n";
        printBorder();
        setColor(7);
        
        cout << "  [1]  Add/Remove Nodes & Edges\n";
        cout << "  [2]  Display Graph Structure\n";
        cout << "  [3]  Find Shortest Path (Dijkstra)\n";
        cout << "  [4]  Find Optimal Path (A*)\n";
        cout << "  [5]  DEMO: Watch Algorithm Work\n";
        cout << "  [6]  Live Updates (Weather/Roads)\n";
        cout << "  [7]  Show Route History\n";
        cout << "  [8]  Load Graph from File\n";
        cout << "  [0]  Exit\n";
        
        printBorder();
        
        setColor(14);
        cout << "\n  >> Enter choice: ";
        setColor(7);
        cin >> choice;

        switch (choice) {
        case 1:
            showHeader();
            ih->startMenu();
            break;

        case 2:
            displayGraphStructure(g);
            break;

        case 3:
            findShortestPath(g, &history);
            break;

        case 4:
            findAStarPath(g, &history);
            break;

        case 5:
            demonstrateAlgorithm(g);
            break;

        case 6:
            showHeader();
            up->updateMenu();
            break;

        case 7:
            showRouteHistory(&history);
            break;

        case 8:
            loadGraphFromFile(g);
            break;

        case 0:
            showHeader();
            setColor(10);
            cout << "\n  Thank you for using NAVEX!\n";
            cout << "  Safe travels!\n\n";
            setColor(7);
            Sleep(1500);
            break;

        default:
            setColor(12);
            cout << "\n  ERROR: Invalid choice! Please try again.\n";
            setColor(7);
            pauseScreen();
        }

    } while (choice != 0);
}