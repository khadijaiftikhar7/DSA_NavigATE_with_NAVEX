#include "Graph.h"
#include "InputHandler.h"
#include "Updater.h"

int main() {
    Graph g;
    InputHandler ih(&g);
    Updater up(&g);

    // start using menus
    ih.startMenu();
    up.updateMenu();

    return 0;
}
