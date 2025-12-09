#define _HAS_STD_BYTE 0

#include "Graph.h"
#include "InputHandler.h"
#include "Updater.h"
#include "WeatherManager.h"
#include "UI.h"

int main() {
    Graph graph;
    InputHandler inputHandler(&graph);
    
    // Disable weather manager temporarily
    Updater updater(&graph);  // ← Remove weatherManager parameter

    runUI(&graph, &inputHandler, &updater);

    return 0;
}