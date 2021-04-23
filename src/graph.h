#ifndef graph_h
#define graph_h

#include <iostream>
#include <list>
#include <vector>
#include <limits.h>
#include <map> 

using namespace std;

class ZNet;

class Graph
{
    int n;
    int V;    // # vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    
    vector<int> levels; // assign level for each vertex
    //bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()
    map<ZNet*,int> level_net2idx;
    map<int,ZNet*> idx2net_level;
    
    
public:
  
    void decrease_adj_level(ZNet* n);
    void set_need2route(ZNet* n);
  //void dump();
    int create_or_get_net2int_mapping(ZNet* n);
    std::vector<ZNet*> get_top_nets();

    Graph(int V);   // Constructor
    void addEdge(ZNet* v, ZNet* w);   // to add an edge to graph
    bool isCyclic();    // returns true if there is a cycle in this graph
};

#endif
