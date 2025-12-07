#include "Graph.h"
#include "InputHandler.h"
#include "Updater.h"
#include "GraphLoader.h"
#include "WeatherManager.h"
#include "UI.h"
#include <iostream>

int main() {
    Graph* g = new Graph();

    GraphLoader::loadNodes(g, "IslamabadNodes.txt");
    GraphLoader::loadEdges(g, "IslamabadEdges.txt");

    cout << "Graph loaded successfully!\n";
    cout << "Total nodes: " << g->getNumberOfNodes() << "\n";

    WeatherManager wm("e9b7b1f6b6d92567ef5dba75682be028");

    InputHandler ih(g);
    Updater up(g, &wm);

    runUI(g, &ih, &up);

    delete g;
    return 0;
}
