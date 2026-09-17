# NAVEX - Smart Navigation System for Islamabad

A console-based navigation system that finds the shortest routes between locations in Islamabad using graph algorithms.
---


### 1. Route History System (`RouteHistory.cpp` & `RouteHistory.h`)

I implemented a route tracking system that remembers user searches:

#### **How it Works:**
- **Data Structures Used:**
  - `vector<pair<string, string>>` - Stores the last 5 routes searched
  - `unordered_map<string, int>` - Counts how many times each route is searched

#### **Key Functions:**

**`addRoute(from, to)`**
- Saves a new route search
- Updates the usage count
- Keeps only the last 5 searches (removes older ones automatically)

**`showRecentRoutes()`**
- Displays the last 5 routes you searched
- Shows them in order from oldest to newest

**`showMostUsedRoute()`**
- Finds which route you searched the most
- Displays the route name and how many times it was used

#### **Example:**
```
User searches: F6 → BLUE (3 times)
User searches: F7 → BAHRIA (1 time)

Most Used Route: F6 -> BLUE (3 times)
```

---

### 2. User Interface System (`UI.cpp`)

I created the complete console interface that makes the program easy to use:

#### **Main Features:**

**Color-Coded Display**
- Different colors for different types of information
- Yellow for headers, Green for success, Red for errors
- Makes the console output easy to read

**Main Menu**
- Clean numbered options (1-8)
- Easy navigation between features
- Clear instructions for users

**Function Highlights:**

**`showHeader()`**
- Displays the NAVEX logo in ASCII art
- Shows program name and version
- Clears screen for clean display

**`displayGraphStructure()`**
- Shows all locations and their connections
- Displays distances between connected locations
- Color-coded for better readability

**`findShortestPath()`**
- Takes user input for source and destination
- Runs Dijkstra's algorithm
- Shows the complete route with distances
- Saves the search to history automatically

**`demonstrateAlgorithm()`**
- **My favorite feature!**
- Shows step-by-step how Dijkstra's algorithm works
- Displays which nodes are being visited
- Shows distance updates in real-time
- Perfect for understanding the algorithm

**`showLoadingAnimation()`**
- Adds visual feedback during calculations
- Creates a progress bar effect
- Makes the app feel responsive

--

##  Learning Outcomes

Through this project, I learned:
- How to implement and visualize graph algorithms
- Managing user interaction in console applications
- Using appropriate data structures for different tasks
- Creating maintainable and modular code
- Working with C++ STL (vectors, maps, pairs)

---

## Technical Details

### Route History Implementation:
- **Time Complexity:** O(1) for adding routes, O(n) for finding most used
- **Space Complexity:** O(n) where n is number of unique routes

### UI Features:
- Windows Console API for colors
- Dynamic screen clearing
- Input validation
- Error handling with user-friendly messages

---

