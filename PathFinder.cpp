#define _HAS_STD_BYTE 0

#include "PathFinder.h"
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;
extern void setColor(int color);

struct PQNode {
    double dist;
    nodeid node;
    bool operator>(const PQNode& o) const { return dist > o.dist; }
};



void visualizeStep(int step, nodeid current, const string& locationName, double distance, 
                   const vector<bool>& visited, int totalNodes) {
    setColor(14);
    cout << "\n  [Step " << step << "] ";
    setColor(11);
    cout << "Visiting: ";
    setColor(10);
    cout << locationName;
    setColor(7);
    cout << " (Distance: " << fixed << setprecision(2) << distance << " km)\n";
    
    // Show visited nodes
    setColor(8);
    cout << "  Visited: ";
    int count = 0;
    for (int i = 0; i < totalNodes; i++) {
        if (visited[i]) count++;
    }
    cout << count << "/" << totalNodes << " nodes\n";
    setColor(7);
    
    Sleep(500); // Pause for visualization
}

void showPriorityQueue(priority_queue<PQNode, vector<PQNode>, greater<PQNode>>& pq_copy, 
                       const Graph& graph) {
    if (pq_copy.empty()) return;
    
    setColor(14);
    cout << "  Queue: [";
    
    vector<PQNode> temp;
    int shown = 0;
    while (!pq_copy.empty() && shown < 3) {
        PQNode node = pq_copy.top();
        pq_copy.pop();
        temp.push_back(node);
        
        setColor(11);
        cout << graph.getLocation(node.node);
        setColor(7);
        cout << "(" << fixed << setprecision(1) << node.dist << ")";
        
        if (!pq_copy.empty() && shown < 2) cout << ", ";
        shown++;
    }
    
    if (!pq_copy.empty()) {
        cout << "...";
    }
    cout << "]\n";
    setColor(7);
}

// --------------------- DIJKSTRA WITH VISUALIZATION ------------------------
PathResult dijkstra(const Graph& graph, nodeid start, nodeid end) {
    PathResult result;
    int n = graph.getNumberOfNodes();

    if (start < 0 || start >= n || end < 0 || end >= n)
        return result;

    const double INF = numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[start] = 0.0;
    priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
    pq.push({0.0, start});

    setColor(11);
    cout << "\n============================================================\n";
    cout << "  DIJKSTRA'S ALGORITHM VISUALIZATION\n";
    cout << "============================================================\n";
    setColor(7);
    
    setColor(10);
    cout << "\n  Source: " << graph.getLocation(start) << "\n";
    cout << "  Destination: " << graph.getLocation(end) << "\n\n";
    setColor(7);
    
    cout << "  Starting traversal...\n";
    Sleep(1000);

    int step = 0;

    while (!pq.empty()) {
        PQNode cur = pq.top(); 
        pq.pop();
        nodeid u = cur.node;

        if (visited[u]) continue;
        visited[u] = true;
        step++;

        // Visualize current step
        visualizeStep(step, u, graph.getLocation(u), dist[u], visited, n);

        if (u == end) {
            setColor(10);
            cout << "\n  >>> DESTINATION REACHED! <<<\n";
            setColor(7);
            Sleep(1000);
            break;
        }

        // Show neighbors being explored
        if (!graph.neighboursList[u].empty()) {
            setColor(14);
            cout << "  Exploring neighbors: ";
            setColor(7);
            
            for (size_t i = 0; i < graph.neighboursList[u].size(); i++) {
                auto& edge = graph.neighboursList[u][i];
                int v = edge.first;
                double w = edge.second;
                
                setColor(11);
                cout << graph.getLocation(v);
                setColor(7);
                
                double nd = dist[u] + w;
                
                if (nd < dist[v]) {
                    dist[v] = nd;
                    parent[v] = u;
                    pq.push({nd, v});
                    
                    setColor(10);
                    cout << "[Updated: " << fixed << setprecision(1) << nd << " km]";
                    setColor(7);
                }
                
                if (i < graph.neighboursList[u].size() - 1) {
                    cout << ", ";
                }
            }
            cout << "\n";
        }
    }

    if (dist[end] == INF) {
        setColor(12);
        cout << "\n  No path exists!\n";
        setColor(7);
        return result;
    }

    // Build path
    result.distance = dist[end];
    result.success = true;

    setColor(11);
    cout << "\n============================================================\n";
    cout << "  RECONSTRUCTING PATH\n";
    cout << "============================================================\n";
    setColor(7);

    for (int cur = end; cur != -1; cur = parent[cur]) {
        result.path.push_back(cur);
        setColor(14);
        cout << "  <- " << graph.getLocation(cur);
        setColor(7);
        if (parent[cur] != -1) {
            cout << " (from " << graph.getLocation(parent[cur]) << ")\n";
        } else {
            cout << " (START)\n";
        }
        Sleep(300);
    }

    reverse(result.path.begin(), result.path.end());
    
    setColor(10);
    cout << "\n  Path reconstruction complete!\n";
    setColor(7);

    return result;
}

// --------------------- HEURISTIC ------------------------
double heuristic(const Graph& graph, nodeid a, nodeid b) {
    Node* A = graph.Nodes[a];
    Node* B = graph.Nodes[b];

    double dx = A->getX() - B->getX();
    double dy = A->getY() - B->getY();

    return sqrt(dx*dx + dy*dy);
}

// --------------------- A* WITH VISUALIZATION ------------------------
PathResult AStar(const Graph& graph, nodeid start, nodeid end) {
    PathResult result;
    int n = graph.getNumberOfNodes();
    
    if (start < 0 || start >= n || end < 0 || end >= n)
        return result;

    const double INF = numeric_limits<double>::infinity();
    vector<double> g(n, INF), f(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    g[start] = 0.0;
    f[start] = heuristic(graph, start, end);

    priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;
    pq.push({f[start], start});

    setColor(11);
    cout << "\n============================================================\n";
    cout << "  A* ALGORITHM VISUALIZATION\n";
    cout << "============================================================\n";
    setColor(7);
    
    setColor(10);
    cout << "\n  Source: " << graph.getLocation(start) << "\n";
    cout << "  Destination: " << graph.getLocation(end) << "\n";
    setColor(14);
    cout << "  Heuristic (straight-line distance): " 
         << fixed << setprecision(2) << heuristic(graph, start, end) << " km\n\n";
    setColor(7);
    
    cout << "  Starting A* traversal...\n";
    Sleep(1000);

    int step = 0;

    while (!pq.empty()) {
        PQNode cur = pq.top(); 
        pq.pop();
        nodeid u = cur.node;

        if (visited[u]) continue;
        visited[u] = true;
        step++;

        // Visualize current step
        setColor(14);
        cout << "\n  [Step " << step << "] ";
        setColor(11);
        cout << "Visiting: ";
        setColor(10);
        cout << graph.getLocation(u);
        setColor(7);
        cout << " | g=" << fixed << setprecision(1) << g[u] 
             << " h=" << heuristic(graph, u, end) 
             << " f=" << f[u] << "\n";
        
        Sleep(500);

        if (u == end) {
            setColor(10);
            cout << "\n  >>> DESTINATION REACHED! <<<\n";
            setColor(7);
            Sleep(1000);
            break;
        }

        // Show neighbors
        if (!graph.neighboursList[u].empty()) {
            setColor(14);
            cout << "  Checking neighbors: ";
            setColor(7);
            
            for (auto& edge : graph.neighboursList[u]) {
                int v = edge.first;
                double w = edge.second;

                double tentative_g = g[u] + w;
                if (tentative_g < g[v]) {
                    g[v] = tentative_g;
                    f[v] = tentative_g + heuristic(graph, v, end);
                    parent[v] = u;
                    pq.push({f[v], v});
                    
                    setColor(11);
                    cout << graph.getLocation(v);
                    setColor(10);
                    cout << "[f=" << fixed << setprecision(1) << f[v] << "] ";
                    setColor(7);
                }
            }
            cout << "\n";
        }
    }

    if (g[end] == INF)
        return result;

    result.distance = g[end];
    result.success = true;

    setColor(11);
    cout << "\n============================================================\n";
    cout << "  PATH FOUND\n";
    cout << "============================================================\n";
    setColor(7);

    for (int cur = end; cur != -1; cur = parent[cur])
        result.path.push_back(cur);

    reverse(result.path.begin(), result.path.end());
    
    return result;
}