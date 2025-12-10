#include "RouteHistory.h"
#include <iostream>
using namespace std;

void RouteHistory::addRoute(const string& from, const string& to) {
    recentRoutes.push_back({from, to});

    string key = from + " -> " + to;
    routeCount[key]++;

    if (recentRoutes.size() > 5) {
        recentRoutes.erase(recentRoutes.begin());
    }
}

void RouteHistory::showRecentRoutes() {
    cout << "\nLast 5 Searched Routes:\n";
    for (auto& r : recentRoutes) {
        cout << r.first << " -> " << r.second << endl;
    }
}

void RouteHistory::showMostUsedRoute() {
    int maxCount = 0;
    string mostUsed;

    for (auto& r : routeCount) {
        if (r.second > maxCount) {
            maxCount = r.second;
            mostUsed = r.first;
        }
    }

    if (mostUsed.empty())
        cout << "No routes searched yet.\n";
    else
        cout << "Most Used Route: " << mostUsed << " (" << maxCount << " times)\n";
}
