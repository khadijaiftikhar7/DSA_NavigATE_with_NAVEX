#pragma once
#include <string>
#include "Graph.h"

class GraphLoader
{
public:
    static void loadNodes(Graph* g, const std::string& filename);
    static void loadEdges(Graph* g, const std::string& filename);
};
