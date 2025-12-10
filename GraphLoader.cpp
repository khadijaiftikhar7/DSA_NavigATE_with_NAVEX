#include "GraphLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

void GraphLoader::loadNodes(Graph* g, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string tag, name;
        double lat, lon;

        ss >> tag;

        if (tag == "NODE")
        {
            ss >> name >> lat >> lon;
            g->addNode(name, lat, lon);
        }
    }
}

void GraphLoader::loadEdges(Graph* g, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string tag, u, v;
        double dist;

        ss >> tag;

        if (tag == "EDGE")
        {
            ss >> u >> v >> dist;
            g->addEdge(u, v, dist);
        }
    }
}
