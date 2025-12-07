// PathFinder.cpp  — rewritten to use Graph::neighboursList, Graph::Nodes and std::priority_queue
#include "PathFinder.h"
#include <bits/stdc++.h>
using namespace std;

// assume nodeid is int; if your project typedefs nodeid, the header should already provide it.
using nodeid_t = nodeid; // keep existing type name (if nodeid is int typedef elsewhere, this is fine)

struct PQNode {
    double dist;
    nodeid node;
    bool operator>(const PQNode& o) const { return dist > o.dist; }
};

// Dijkstra
vector<nodeid> dijkstra(const Graph& graph, nodeid start, nodeid end) {
    int n = graph.getNumberOfNodes(); // use existing Graph API
    if (start < 0 || start >= n || end < 0 || end >= n) return {};

    const double INF = numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0.0;
    priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        PQNode cur = pq.top(); pq.pop();
        nodeid u = cur.node;
        double d = cur.dist;

        if (d > dist[u]) continue;
        if (u == end) break;
        visited[u] = true;

        // neighboursList is public vector<vector<pair<int,double>>>
        const auto& neighbors = graph.neighboursList[u];
        for (const auto& edge : neighbors) {
            int v = edge.first;
            double w = edge.second;
            if (visited[v]) continue;
            double nd = dist[u] + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    if (dist[end] == INF) return {}; // unreachable

    vector<nodeid> path;
    for (int cur = end; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}

// heuristic for A* using node coordinates (Node has getX/getY())
double heuristic(const Graph& graph, nodeid a, nodeid b) {
    // access Node* from graph.Nodes
    if (a < 0 || b < 0 || a >= graph.getNumberOfNodes() || b >= graph.getNumberOfNodes()) return 0.0;
    Node* A = graph.Nodes[a];
    Node* B = graph.Nodes[b];
    double dx = double(A->getX()) - double(B->getX());
    double dy = double(A->getY()) - double(B->getY());
    return sqrt(dx*dx + dy*dy);
}

// A*
vector<nodeid> AStar(const Graph& graph, nodeid start, nodeid end) {
    int n = graph.getNumberOfNodes();
    if (start < 0 || start >= n || end < 0 || end >= n) return {};

    const double INF = numeric_limits<double>::infinity();
    vector<double> g(n, INF);
    vector<double> f(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    g[start] = 0.0;
    f[start] = heuristic(graph, start, end);

    priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
    pq.push({f[start], start});

    while (!pq.empty()) {
        PQNode cur = pq.top(); pq.pop();
        nodeid u = cur.node;
        if (visited[u]) continue;
        if (u == end) break;
        visited[u] = true;

        const auto& neighbors = graph.neighboursList[u];
        for (const auto& edge : neighbors) {
            int v = edge.first;
            double w = edge.second;
            double tentative_g = g[u] + w;
            if (tentative_g < g[v]) {
                g[v] = tentative_g;
                f[v] = tentative_g + heuristic(graph, v, end);
                parent[v] = u;
                pq.push({f[v], v});
            }
        }
    }

    if (g[end] == INF) return {}; // unreachable

    vector<nodeid> path;
    for (int cur = end; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}
