#ifndef graph_h
#define graph_h

//////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                     //
//////////////////////////////////////////////////////////////////////////////////////
// User created library
#include "connectivity.h" //NOTE: Add connectivity.h and remove ZNet class primitives
// Standard library
#include <map> 
#include <list>
#include <vector>
#include <limits.h>
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////
//                       Declare Class and Its Attributes                           //
//////////////////////////////////////////////////////////////////////////////////////
class Graph {
    // Declare attributes
    int n;
    int V; // Number of graph vertices
    list<int> *adj; // Pointer to list of adjacency array
    vector<int> levels; // Level of each graph vertex
    map<ZNet*,int> level_net2idx; // Variable for mapping net to index
    map<int,ZNet*> idx2net_level; // Variable for mapping index to net
    //bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()

  public:
    // Declare constructor
    Graph(int V);

    // Declare methods
    bool isCyclic(); // Method for checking whether there is a cyclic connection or not
    void set_need2route(ZNet* n); // Method for setting net level to 0 (route immediately)
    void decrease_adj_level(ZNet* n); // Method for decreasing adjacency level of neighboring nets
    std::vector<ZNet*> get_top_nets(); // Method for getting VCG top nets
    int create_or_get_net2int_mapping(ZNet* n); // Getter method for getting int index of a net
    void addEdge(ZNet* v, ZNet* w); // Method for adding edge between vertices
};

#endif
