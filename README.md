this file is for my Node class. a node basically stores info about one point in the graph. every node has an index, a name, distanceFromSource, previousNode, visited flag, and x/y coordinates.

there are 3 constructors:

one where i give index + name

one where i only give index (name becomes “Unknown”)

one where i give index + name + x,y

all constructors set distanceFromSource to 0, previousNode to nullptr, visited to false, and x,y to whatever I give (or 0).

there are simple getter functions to get index, name, distanceFromSource, previousNode, visited status, and x,y.

there are setter functions too: set name, set visited, set previous node, set distance, and set x,y.
