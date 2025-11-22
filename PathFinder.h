#pragma once
#include <vector>
#include "Graph.h" //importing this from Kdj iftikhar
using namespace std;

using nodeid=int; 
vector<nodeid> Dijkstra( const Graph& graph, nodeid start, nodeid end);
vector<nodeid> AStar(const Graph& graph, nodeid start, nodeid end);