this file has my Graph class code. i made this to add nodes and edges and remove them. every node gets an index by itself with idxCounter. i store all nodes in a vector and all edges in an adjacency list.

when i add a node, it just pushes it in the vector and increases the counter. i can add a node with name, or name + x,y, or just x,y (then name is “Unknown”). numberOfNodes also increases.

for edges, i give source and destination names, then the graph finds their index and adds the edge in neighboursList with a weight. nothing complicated.

removing edges: i check the source node’s list and remove the matching destination. there is also a function to remove all edges of a node (both ways).

removing a node: first remove its edges, then remove the node itself from the vector and from the neighbours list. then update indices in the adjacency list because when a node is deleted, all the nodes after it shift one step back.

getIndex() just finds a node by name and returns its index.
getLocation() returns name if index is valid.
getNumberOfNodes() returns total nodes.

this is basically it. it’s just a simple graph class i made with add/remove for nodes and edges.
