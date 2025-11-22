#include "PathFinder.h"
#include<bits/stdc++.h>
using namespace std;

struct HeapNode{ //representing one entry in the heap
    double distance;
    nodeid node;
};
//I AM USING PRIORITY QUEUE VIA MIN HEAP 
class MinHeap {
 public:
vector<HeapNode> heap;   //heap array

bool empty() const {
return heap.empty();  //empty
    }

//It returns the smallest element
HeapNode top() const {
return heap[0];
    }

//Insert a new node
void push(const HeapNode& x) {
heap.push_back(x);
heapifyUp(heap.size() - 1);
    }

//Remove smallest element
void pop() {
 if (heap.empty()) return;

//Move last element to root
 heap[0] = heap.back();
heap.pop_back();

 if (!heap.empty()) {
 heapifyDown(0);
        }
    }
 private:

 //Maintain heap upwards
void heapifyUp(int i) {
 while (i > 0) {
 int parent = (i - 1) / 2;
 if (heap[i].distance < heap[parent].distance) {
swap(heap[i], heap[parent]);
i = parent;
 } else {
 break;
            }
        }
    }

// Maintain heap downwards
 void heapifyDown(int i) {
int n = heap.size();

 while (true) {
 int left = 2 * i + 1;
 int right = 2 * i + 2;
 int smallest = i;

 if (left < n && heap[left].distance < heap[smallest].distance) {
 smallest = left;
            }
 if (right < n && heap[right].distance < heap[smallest].distance) {
smallest = right;
            }

if (smallest != i) {
swap(heap[i], heap[smallest]);
i = smallest;
} else {
  break;
    }
        }
    }
};


vector<nodeid> dijkstra(const Graph& graph, nodeid start, nodeid end)
{ int n= graph.getNumNodes(); //importing from kdj iftikhar
 double extreme= numeric_limits<double>::infinity(); //assuming infinite distance 
vector<double> distance(n , extreme);
vector<nodeid> parent(n,-1);
distance[start]=0;

MinHeap mh;
mh.push({0.0, start});
 //Creating a visited flag to keep track of nodes
    vector<bool> visited(n, false);

while (!mh.empty()) {
    HeapNode top = mh.top(); //node with the smallest distance
     mh.pop();

    nodeid u = top.node;
    double d = top.distance;

    //Compare value to check if a better option is available
  if (d > distance[u]) continue;

 //if already found the destination break the loop
  if (u==end)
  break;
  visited[u]=true //this will not let me visit it again

  //Looping through its neigbours
  const auto& neighbors= graph.getNeighbours(u);
  
  //Getting the weight and id of neighbors
  for (const auto& edge: neighbors){
    nodeid v =edge.first; //this gives the id
    double w= edge.second; //this gives the weight

    if(visited[v]){ continue;} //no need to reprocess

    //Distance if travelled through this path
    double newDistance = distance[u]+w;

    //if the newfound path is better, update the shortest path
    if (newDistance <distance[v]){
        distance[v]= newDistance;
        parent[v]=u;}

        mh.push({newDistance, v}); //pushing the neighbor in the heap


        //handling unreachable scenarios
        if(distance[end]==extreme){
            return {}
        }

        //Reconstructing the path from end to start
        vector<nodeid> track;
        for(nodeid current =end; current!= -1; current=parent[current]){
            track.push_back(current);
        }

        //Rectifying the order using reverse function
        reverse(track.begin(),track.end());

        return track; //My shortest path
    }
  }
}

vector<nodeid> AStar (const Graph& graph, nodeid start, nodeid end){


    return {};
}