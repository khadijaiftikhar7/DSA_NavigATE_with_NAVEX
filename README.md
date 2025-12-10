this file is for my InputHandler class. it basically deals with user input for the graph. instead of putting input code in the main file, i made this class to keep things cleaner.

the constructor just takes a pointer to the graph so it can call graph functions.

there are some small validation functions:

isValidName() -> checks if a name is not empty and only has letters, numbers, or _

isValidWeight() -> weight must be > 0

then i have functions that handle different menu tasks:

handleAddNode()
asks user for a node name, checks if it’s valid, then adds it to the graph.

handleAddEdge()
asks for source, destination, and weight. checks everything and adds an edge.

handleRemoveNode()
asks for a node name and removes it if it exists.

handleRemoveEdge()
asks for two node names and removes the edge between them.

displayNodes()
prints all the node names in the graph.

displayNeighbours()
asks for a node name, finds its index, and prints all neighbours with their weights.

startMenu()
this is the main loop. it shows a menu with options like add node, add edge, remove node, etc. the user picks a number and it calls the right function. 0 exits the program.
