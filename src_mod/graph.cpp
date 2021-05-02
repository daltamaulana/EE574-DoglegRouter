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

// NOTE: Method for increasing adjacency level of neighboring nets
void Graph::increase_adj_level(ZNet* n) {
	// Get parent net index
	int i = create_or_get_net2int_mapping(n);
	// Reduce child net level
	for(list<int>::iterator j = adj[i].begin(); j!=adj[i].end(); ++j) {
		levels[*j]++;
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

	// Check nets level
	if (levels[V] >= levels[W]) {
		// Add net to adjacency list
		adj[V].push_back(W); 
		// Increase net level based on parent net
		levels[W] = levels[V] + 1; // NOTE: This part changed from levels[W]++
		// Increase net level which connected to w net
		for(list<int>::iterator iter = adj[W].begin(); iter!=adj[W].end(); ++iter) {
			ZNet* neighbor_net = idx2net_level[(*iter)];
			// Call increase_adj_level method
			increase_adj_level(neighbor_net);
		}
	}
}

// NOTE: Method for performing transitive reduction operation on the graph
void Graph::transitiveReduction() {
	// NOTE: Debug purpose
	for(int i=0; i<V; i++) {
		std::cout << "Index: " << i << "\tNet name: " << idx2net_level[i]->get_name() << std::endl;
	}
	// Iterate through each net adjacency list
	for(int i=0; i<V; i++) {
		// NOTE: Debug purpose
		std::cout << "Net: " << idx2net_level[i]->get_name() << " Adjacency list: ";
		// Iterate through adjacency list
		for(list<int>::iterator iter = adj[i].begin(); iter!=adj[i].end(); ++iter) {
			std::cout << idx2net_level[*iter]->get_name() << " ";
		}
		std::cout << "\n" << std::endl;

		// Create remove_if list iterator
		adj[i].remove_if([this, i](int iter) {
			return (levels[iter]-levels[i]) > 1;
		});

		// Iterate through adjacency list
		for(list<int>::iterator iter = adj[i].begin(); iter!=adj[i].end(); ++iter) {
			// Loop to removing edge
		}
	}
}

// NOTE: Method for getting vertices count
void Graph::printGraph() {
	// Print graph
	for(int i=0; i<V; i++) {
		std::cout << "Net " << idx2net_level[i]->get_name() << "-> Level: " << levels[i] << " \tAdjacency list: ";
		for(auto iter = adj[i].begin(); iter != adj[i].end(); ++iter) {
			std::cout << idx2net_level[*iter]->get_name() << " ";
		}
		std::cout << "\n" << std::endl;
	}
}
 

