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

// Returns true if the graph contains a cycle, else false.
// This function is a variation of DFS() in http://www.geeksforgeeks.org/archives/18212
bool Graph::isCyclic()
{
	// You have to implement here!!
}
 
int Graph::create_or_get_net2int_mapping(ZNet* net) {
	// numbering a net
	if (level_net2idx.find(net) == level_net2idx.end() )
		++n,level_net2idx[net] = n,idx2net_level[n]=net;

	return level_net2idx[net];
}


std::vector<ZNet*> Graph::get_top_nets() {
	
	std::vector<ZNet*> nets;

	for(int i=0;i<V;i++) {
		if ( levels[i] == 0 ) {
			levels[i]=-1;
			nets.push_back(idx2net_level[i]);
		}
	}

	return nets;        
}


void Graph::decrease_adj_level(ZNet* n) {
	int i = create_or_get_net2int_mapping(n);
	for(list<int>::iterator j = adj[i].begin(); j!=adj[i].end(); ++j) {
		levels[*j]--;
	}
}

void Graph::set_need2route(ZNet* n) {
	levels[level_net2idx[n]]=0;
}
  
void Graph::addEdge(ZNet* v, ZNet* w)
{
     int V = create_or_get_net2int_mapping(v);
     int W = create_or_get_net2int_mapping(w);
     
    adj[V].push_back(W); 
    levels[W]++;
}
 

