#ifndef ROUTE_HISTORY_H
#define ROUTE_HISTORY_H

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class RouteHistory {
private:
    vector<pair<string, string>> recentRoutes;
    unordered_map<string, int> routeCount;

public:
    void addRoute(const string& from, const string& to);
    void showRecentRoutes();
    void showMostUsedRoute();
};

#endif
