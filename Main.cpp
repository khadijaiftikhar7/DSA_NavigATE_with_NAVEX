// 1. Prevent Windows macro bloat
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

// 2. (Optional on g++ — can remove) _HAS_STD_BYTE is MSVC-specific
// #define _HAS_STD_BYTE 0 

// 👉 Include UI.h (and thus <windows.h>) **before** any header that might do `using namespace std;`
#include "UI.h"

// Now include the rest
#include "Graph.h"
#include "InputHandler.h"
#include "Updater.h"
#include "WeatherManager.h"

int main() {
    Graph graph;
    InputHandler inputHandler(&graph);
    Updater updater(&graph);  // weather temporarily disabled
    runUI(&graph, &inputHandler, &updater);
    return 0;
}
