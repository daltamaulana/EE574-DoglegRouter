//////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                     //
//////////////////////////////////////////////////////////////////////////////////////
// User created library
#include "graph.h"
#include "connectivity.h"
// Standard library
#include <iostream>
#include <list>
#include <limits.h>

//////////////////////////////////////////////////////////////////////////////////////
//                         Define Class and Its Methods                             //
//////////////////////////////////////////////////////////////////////////////////////
// Class constructor
Graph::Graph(int V) {
	// Initialize paramters
	n = -1;
	this->V = V;
	// Create new adjacency list for each vertex
	adj = new list<int>[V];
	// Resize levels vector and assign with 0 value
	levels.resize(V);
	for(int i=0;i<V;i++)  {
		levels[i] = 0;  		
	}
}

// Method for checking cyclic dependencies in graph
bool Graph::isCyclic() {
	// You have to implement here!!
}

// Method for setting net level to 0 (route immediately)
void Graph::set_need2route(ZNet* n) {
	// Set net level to 0
	levels[level_net2idx[n]] = 0;
}

// Method for decreasing adjacency level of neighboring nets
void Graph::decrease_adj_level(ZNet* n) {
	// Get parent net index
	int i = create_or_get_net2int_mapping(n);
	// Reduce child net level
	for(list<int>::iterator j = adj[i].begin(); j!=adj[i].end(); ++j) {
		levels[*j]--;
	}
}

// Method for getting top nets in the graph
std::vector<ZNet*> Graph::get_top_nets() {
	// Declare local variable
	std::vector<ZNet*> nets;
	// Loop through net lists
	for(int i=0;i<V;i++) {
		if ( levels[i] == 0 ) {
			levels[i]=-1;
			nets.push_back(idx2net_level[i]);
		}
	}
	// Return value
	return nets;        
}

// Getter method for getting int index of a net
int Graph::create_or_get_net2int_mapping(ZNet* net) {
	// Create new net map if net is new
	if (level_net2idx.find(net) == level_net2idx.end() )
		++n, level_net2idx[net] = n, idx2net_level[n]=net;
	// Return value
	return level_net2idx[net];
}

// Method for adding edge between vertices
void Graph::addEdge(ZNet* v, ZNet* w)
{
	// Find index of the net 
	int V = create_or_get_net2int_mapping(v);
	int W = create_or_get_net2int_mapping(w);
    
	// Add net to adjacency list
    adj[V].push_back(W); 
	// Increase net level
    levels[W]++;
}
 

