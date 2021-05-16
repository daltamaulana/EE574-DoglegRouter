#ifndef graph_h
#define graph_h

//////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                     //
//////////////////////////////////////////////////////////////////////////////////////
// User created library
#include "connectivity.h"
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
  list<int> *adj; // Pointer to list of adjacency list
  list<int> *trans_adj; // Pointer to list of transposed adjacency list
  vector<int> levels; // Level of each graph vertex
  map<ZNet*,int> level_net2idx; // Variable for mapping net to index
  map<int,ZNet*> idx2net_level; // Variable for mapping index to net

  public:
    // Declare constructor
    Graph(int V);

    // Declare methods
    bool isCyclic(); // Method for checking whether there is a cyclic connection or not
    bool isNodeCyclic(int idx, bool visited_node[], bool *node_stack); // Helper method for checking cyclic connection
    void set_need2route(ZNet* n); // Method for setting net level to 0 (route immediately)
    void decrease_adj_level(ZNet* n); // Method for decreasing adjacency level of neighboring nets
    void increase_adj_level(ZNet* n); // NOTE: Method for increasing adjacency level of neighboring nets
    std::vector<ZNet*> get_top_nets(); // Method for getting VCG top nets
    int create_or_get_net2int_mapping(ZNet* n); // Getter method for getting int index of a net
    void addEdge(ZNet* v, ZNet* w); // Method for adding edge between vertices
    void addVertex(ZNet* v); // Method for adding vertex
    void removeVertex(ZNet* v); // Method for removing vertex
    void transitiveReduction(); // NOTE: Method for performing transitive reduction on graph
    void printGraph(); // NOTE: Method for printing graph
    void printTransposedGraph(); //NOTE: Method for printing transposed graph
    void transposeGraph(); // NOTE: Method for transposing graph

};

#endif