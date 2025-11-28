#include "Updater.h"
#include <iostream>

Updater::Updater(Graph* g) {
    graph = g;
    currentWeather = CLEAR;
}

// --------------------------------------------
// WEATHER FUNCTIONS
// --------------------------------------------
void Updater::setWeather(Weather w) {
    currentWeather = w;
    applyWeatherEffects();
}

void Updater::applyWeatherEffects() {

    for (int i = 0; i < graph->getNumNodes(); i++) {
        for (auto& edge : graph->neighboursList[i]) {

            if (currentWeather == CLEAR) continue;

            if (currentWeather == RAIN) {
                edge.second *= 1.2;
            }
            else if (currentWeather == STORM) {
                edge.second *= 2.0;
            }
            else if (currentWeather == FLOOD) {
                // Flood blocks certain roads entirely
                edge.second = 1e9;  // treat as blocked
            }
        }
    }

    std::cout << "Weather-based weight adjustments applied.\n";
}

// --------------------------------------------
// ROAD UPDATES
// --------------------------------------------
void Updater::updateEdgeWeight(const std::string& src, const std::string& dest, double newWeight) {
    int u = graph->getIndex(src);
    int v = graph->getIndex(dest);

    if (u == -1 || v == -1) return;

    for (auto& edge : graph->neighboursList[u]) {
        if (edge.first == v) {
            edge.second = newWeight;
            break;
        }
    }

    std::cout << "Edge weight updated.\n";
}

void Updater::blockRoad(const std::string& src, const std::string& dest) {
    graph->removeEdge(src, dest);
    std::cout << "Road blocked.\n";
}

void Updater::unblockRoad(const std::string& src, const std::string& dest, double weight) {
    graph->addEdge(src, dest, weight);
    std::cout << "Road unblocked.\n";
}

// --------------------------------------------
// VIP ZONE RESTRICTIONS
// --------------------------------------------
void Updater::addRestrictedZone(const std::string& zoneName) {
    restrictedZones.insert(zoneName);
    std::cout << zoneName << " added as restricted zone.\n";
}

void Updater::clearRestrictedZones() {
    restrictedZones.clear();
    std::cout << "VIP restrictions cleared.\n";
}

// --------------------------------------------
// RE-ROUTING
// --------------------------------------------
void Updater::reRoute(const std::string& source, const std::string& dest) {

    int src = graph->getIndex(source);
    int dst = graph->getIndex(dest);

    auto path = Dijkstra(*graph, src, dst);

    if (path.empty()) {
        std::cout << "No available path.\n";
        return;
    }

    std::cout << "Shortest Path:\n";
    for (int id : path) {
        std::cout << graph->getLocation(id) << " -> ";
    }
    std::cout << "END\n";
}

// --------------------------------------------
// MENU
// --------------------------------------------
void Updater::updateMenu() {
    int choice;

    do {
        std::cout << "\n--- LIVE UPDATE MENU ---\n";
        std::cout << "1. Change Weather\n";
        std::cout << "2. Block Road\n";
        std::cout << "3. Unblock Road\n";
        std::cout << "4. Update Edge Weight\n";
        std::cout << "5. Add VIP Restricted Zone\n";
        std::cout << "6. Clear VIP Zones\n";
        std::cout << "7. Recalculate Route\n";
        std::cout << "0. Exit\n";

        std::cin >> choice;

        if (choice == 1) {
            int w;
            std::cout << "Weather (0 Clear, 1 Rain, 2 Storm, 3 Flood): ";
            std::cin >> w;
            setWeather((Weather)w);
        }
        else if (choice == 2) {
            std::string a,b;  
            std::cin >> a >> b;
            blockRoad(a,b);
        }
        else if (choice == 3) {
            std::string a,b;  
            double w;
            std::cin >> a >> b >> w;
            unblockRoad(a,b,w);
        }
        else if (choice == 4) {
            std::string a,b;  
            double w;
            std::cout << "src dest weight: ";
            std::cin >> a >> b >> w;
            updateEdgeWeight(a,b,w);
        }
        else if (choice == 5) {
            std::string z;
            std::cin >> z;
            addRestrictedZone(z);
        }
        else if (choice == 6) {
            clearRestrictedZones();
        }
        else if (choice == 7) {
            std::string a,b;
            std::cin >> a >> b;
            reRoute(a,b);
        }

    } while (choice != 0);
}
