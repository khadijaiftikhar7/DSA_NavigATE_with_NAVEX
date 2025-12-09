#define _HAS_STD_BYTE 0
#ifndef UPDATER_H
#define UPDATER_H

#include "Graph.h"
#include "PathFinder.h"
#include <string>
#include <unordered_set>

// Forward declaration
class WeatherManager;

enum Weather { CLEAR, RAIN, STORM, FLOOD };

class Updater {
private:
    Graph* graph;
    WeatherManager* weatherManager;
    Weather currentWeather;
    std::unordered_set<std::string> restrictedZones;

public:
    Updater(Graph* g);
    Updater(Graph* g, WeatherManager* wm);

    // WEATHER HANDLING
    void setWeather(Weather w);
    void applyWeatherEffects();
    void updateWeatherRealTime();

    // ROAD / EDGE UPDATE
    void updateEdgeWeight(const std::string& src, const std::string& dest, double newWeight);
    void blockRoad(const std::string& src, const std::string& dest);
    void unblockRoad(const std::string& src, const std::string& dest, double weight);

    // VIP RESTRICTIONS
    void addRestrictedZone(const std::string& zoneName);
    void clearRestrictedZones();

    // REAL-TIME RE-ROUTING
    void reRoute(const std::string& source, const std::string& dest);

    // MENU/UI
    void updateMenu();
};

#endif