#ifndef ROUTE_HISTORY_H
#define ROUTE_HISTORY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

class RouteHistory {
private:
    std::vector<std::pair<std::string, std::string>> recentRoutes;
    std::unordered_map<std::string, int> routeCount;

public:
    void addRoute(const std::string& from, const std::string& to);
    void showRecentRoutes();
    void showMostUsedRoute();
};

#endif // ROUTE_HISTORY_H
