#include "PathFinder.h"
#include<bits/stdc++.h>
using namespace std;

struct HeapNode{
    double distance;
    nodeid node;
};
//USING PRIORITY QUEUE VIA MIN HEAP
vector<HeapNode> heap;

bool empty(){
    return heap.empty(); //this tells us if the heap is empty
}

HeapNode top(){ //this returns the root element
    return heap[0];
}
void push( const HeapNode& x){ //inserting new element
    heap.push_back(x);
    heapifyUP( heap.size()-1);
}
void pop(){
    if (heap.empty()) return;

    heap[0]=heap.back(); //copying last element to the root
    heap.pop_back(); //removing last element
    if(!heap.empty()){
        heapifyDOWN(0); //pushing new root down until heap property is valid
    }
}

//it moves a node upward until it satisfies heap property
void heapifyUP(int x){
    while(x>0){
int parent= (x-1)/2;
if (heap[x].distance <heap[parent].distance){
    swap(heap[x], heap[parent]);
    x=parent;
}
else{
    break;
}
    }
}
//it moves a node downwards until it satisfies heap property

void heapifyDOWN(int x){
    int n= heap.size();
    while(1){
        int left =2*x +1;
        int right=2*x +2;
        int smallest=x;

        if(left< n && heap[left].distance < heap[smallest].distance){
            smallest=left;
        }
        if (right< n && heap[right].distance < heap[smallest].distance){
            smallest=right;
        }
        if (smallest !=x){
            swap(heap[x], heap[smallest]);
            x=smallest;
        }
        else{
            break;
        }
    }
}
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
  visited[u]=true ;//this will not let me visit it again

  //Looping through its neigbours
  const auto& neighbors= graph.getNeighbors(u);
  
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
        parent[v]=u;
        mh.push({newDistance, v}); //pushing the neighbor in the heap
    }

    
}
      //handling unreachable scenarios
        if(distance[end]==extreme){
            return {};
        }

        //Reconstructing the path from end to start
        vector<nodeid> track;
        for(nodeid current_best =end; current_best!= -1; current_best=parent[current_best]){
            track.push_back(current_best);
        }

        //Rectifying the order using reverse function
        reverse(track.begin(),track.end());

        return track; //My shortest path
  
}
}
double heuristic( const Graph& graph , nodeid a, nodeid b){
    auto A =graph.getNode(a);
    auto B= graph.getNode(b);

    double d1= A.x -B.x;
    double d2= A.y -B.y;
    return sqrt(d1*d1  +d2*d2); //Euclidean distance
}


//A Star is dijkstra with heuristics
vector<nodeid> AStar (const Graph& graph, nodeid start, nodeid end){
int n= graph.getNumNodes();
double extreme= numeric_limits<double>::infinity();
    
vector<double> g( n, extreme);//greedy score
vector<double> f( n,extreme) ;//g + heuristics
vector<nodeid> parent( n ,-1); //previous node on the best path

g[start]=0;
f[start]= heuristic( graph, start, end);

MinHeap mh;
mh.push({ f[start], start});
vector<bool> visited(n, false); //flag for visited

while(!mh.empty()){
    HeapNode top=mh.top();
    mh.pop();

    nodeid u=top.node;

    if(u == end)
    break; //if the node i processed from the heap is the goal i break the cycle

    if(visited[u]){
        continue;
    }
    visited[u]=true;
    const auto& neighbors= graph.getNeighbors(u);  //exploring neighbors 
   
    for(  const auto& edge: neighbors){  //looping through all neighbor edges
        nodeid v= edge.first;
        double w= edge.second;
    
    double current_best =g[u]+ w;
    if (current_best < g[v]){
        g[v]=  current_best;
        f[v]= current_best+ heuristic(graph,v,end);
        parent[v]= u; //best path to v from u
        mh.push({f[v], v}); //puhsing v into heap  with new priority
    }
}
      
}
  if(g[end] == extreme)
        return {};

        //Reconstruction of path
 vector<nodeid> track;
 for(nodeid current_best =end; current_best!= -1; current_best= parent[current_best]){
track.push_back(current_best);
    }

    reverse(track.begin(), track.end());
    return track;


}