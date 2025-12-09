#define _HAS_STD_BYTE 0
#ifndef UI_H
#define UI_H

#include "Graph.h"
#include "InputHandler.h"
#include "Updater.h"
#include "RouteHistory.h"
#include "GraphLoader.h"
#include <windows.h>

void runUI(Graph* g, InputHandler* ih, Updater* up);

#endif