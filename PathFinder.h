#pragma once
#include <vector>
#include "Graph.h"

using nodeid = int;

struct PathResult {
    std::vector<nodeid> path;
    double distance;
    bool success;

    PathResult() : distance(0), success(false) {}
};

PathResult dijkstra(const Graph& graph, nodeid start, nodeid end);
PathResult AStar(const Graph& graph, nodeid start, nodeid end);
