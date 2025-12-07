#include "UI.h"
#include <iostream>
using namespace std;

void runUI(Graph* g, InputHandler* ih, Updater* up) {
    RouteHistory history;

    int choice;
    do {
        cout << "\n========== NAVEX MAIN MENU ==========\n";
        cout << "1. Graph Operations\n";
        cout << "2. Live Updates\n";
        cout << "3. Find Route (Demo Entry)\n";
        cout << "4. Show Last 5 Routes\n";
        cout << "5. Show Most Used Route\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string from, to;

        switch (choice) {
        case 1:
            ih->startMenu();
            break;

        case 2:
            up->updateMenu();
            break;

        case 3:
            cout << "Enter Source: ";
            cin >> from;
            cout << "Enter Destination: ";
            cin >> to;

            history.addRoute(from, to);

            cout << "Route Stored Successfully!\n";
            break;

        case 4:
            history.showRecentRoutes();
            break;

        case 5:
            history.showMostUsedRoute();
            break;

        case 0:
            cout << "Exiting NAVEX...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}
