#include<bits/stdc++.h>
using namespace std;
struct Edge;
struct Node {

    string name;
    int distance; //its the distance from the source node
    Node* previous;
    bool visited; //checks if its explored or not
    vector <Edge*> edges;  //edges outgoing from the node

    
    Node(string n) {
        name = n;
        distance = INT_MAX; //initializing distance to infinity
        previous = nullptr;
        visited = false;
        
    }
};

struct Edge{
    int weight;
    Node* destination; //destination

    Edge( int w,  Node* d){
        weight=w;
        destination= d;
    }
};

struct Graph{

    vector <Node*> Nodes;

    Node* addNode( string n){ //adding new nodes
        Node* newNode= new Node(n);
        Nodes.push_back(newNode);
        cout<<newNode->name<<" has been added succesfully"<<endl;
        return newNode;
    }
    void addEdge(int w, Node* source, Node *destination){  //adding new edges

    if (!source || !destination){   //INVALID CASE ACCOUNTABILITY
cout<<" Cannot add edge for the given parameters"<<endl;
return;
    }
        Edge* newEdge= new Edge(w ,destination);
        source->edges.push_back( newEdge);
        cout<<newEdge<<" has been created from "<<source<< "to"<< destination<<endl;
    }

    void display(){
        int count =0;
        for( auto n: Nodes){
            cout<<n->name<<" ---->";
            for( auto ed: n->edges){
                cout<<ed->weight<<"--->"<<ed->destination->name; //linking the destination from the edge to the name of the node
            }
            cout<<endl;
        }
    }
    void Reset(){ //reseting the whole graph
        for(auto nodes: Nodes){
            nodes->distance= INT_MAX;
            nodes->previous= nullptr;
            nodes->visited= false;
        }
    }  
};




