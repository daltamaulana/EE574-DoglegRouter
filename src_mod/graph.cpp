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
	trans_adj = new list<int>[V];
	// Resize levels vector and assign with 0 value
	levels.resize(V);
	for(int i=0;i<V;i++)  {
		levels[i] = 0;  		
	}
}

// NOTE: Method for checking cyclic dependency of a graph (Reference: CodeGeeks)
bool Graph::isCyclic() {
	// Declare local variable
	bool *visited_node = new bool[this->V];
	bool *node_stack = new bool[this->V];

	// Initialize array value
	for(int i=0; i<this->V; i++) {
		visited_node[i] = false;
		node_stack[i] = false;
	}

	// Check each vertices adjacency array to detect cyclic path
	for(int i=0; i<this->V; i++) {
		// Call function
		if (isNodeCyclic(i, visited_node, node_stack)) {
			return true;
		}
	}

	// No cycle connection detected
	return false;
}

// NOTE: Helper function for checking cyclic path
bool Graph::isNodeCyclic(int idx, bool visited_node[], bool *node_stack) {
	// Check whether vertex was visited or not
	if (!visited_node[idx]) {
		// Set current vertex as visited
		visited_node[idx] = true;
		node_stack[idx] = true;

		// Iterate through adjacency list
		for(auto iter = adj[idx].begin(); iter != adj[idx].end(); ++iter) {
			if (!visited_node[*iter] && isNodeCyclic(*iter, visited_node, node_stack)) {
				return true;
			} else if (node_stack[*iter]) {
				return true;
			} else {
				continue;
			}
		}
	}

	// Remove vertex from node stack
	node_stack[idx] = false;
	return false;
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
		// Search for transitive edge
		auto iter = std::find_if(trans_adj[*j].begin(), trans_adj[*j].end(), [i](int idx) {
			return idx == i;
		});

		if (trans_adj[*j].size() == 1) {
			if ((levels[*j] - levels[i]) > 0) {
				levels[*j]--;
			}
		} else if ((trans_adj[*j].size() == 2) && (*iter == i)) {
			if ((levels[*j] - levels[i]) > 0) {
				levels[*j]--;
			}
		} else {
			continue;
		}

		// Call increase_adj_level method recursively for each vertex in adjacency list
		decrease_adj_level(idx2net_level[*j]);
	}
}

// NOTE: Method for increasing adjacency level of neighboring nets
void Graph::increase_adj_level(ZNet* n) {
	if (!isCyclic()) {
		// Get parent net index
		int i = create_or_get_net2int_mapping(n);
		// Reduce child net level
		for(list<int>::iterator j = adj[i].begin(); j!=adj[i].end(); ++j) {
			// Increase child level if the level difference between parent and child is less than 2
			if ((levels[*j] - levels[i]) < 2) {
				levels[*j]++;
			}

			// Call increase_adj_level method recursively for each vertex in adjacency list
			increase_adj_level(idx2net_level[*j]);
		}
	}
}

// Method for getting top nets in the graph
std::vector<ZNet*> Graph::get_top_nets() {
	// NOTE: Print nets
	for(int i=0; i<V; i++) {
		std::cout << "Nets: " << idx2net_level[i]->get_name() << std::endl;
	}

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
		
		// Increase level of child net adjacent vertices
		increase_adj_level(w);

		// Increase child net level based on parent net
		levels[W] = levels[V] + 1;

	} else {
		// Add net to adjacency list without increasing child level
		adj[V].push_back(W);
	}
}

// Method for adding vertex to graph
void Graph::addVertex(ZNet* v) {
	// Create vertex
	create_or_get_net2int_mapping(v);
}

// Method for removing vertex from graph
void Graph::removeVertex(ZNet* v) {
	// Create vertex
	int V = create_or_get_net2int_mapping(v);

	// Clear adjacency list
	adj[V].clear();
}

// NOTE: Method for transposing graph
void Graph::transposeGraph() {
	// Clear transposed adjacency matrix
	for(int i=0; i<V; i++) {
		trans_adj[i].clear();
	}
	
	// Iterate through adjacency list
	for(int i=0; i<V; i++) {
		for(auto iter=adj[i].begin(); iter!=adj[i].end(); ++iter) {
			// Add edge to transposed adjacency list
			trans_adj[*iter].push_back(i);
		}
	}
}

// NOTE: Method for getting vertices count
void Graph::printGraph() {
	// Print graph
	std::cout << "************************************************************************" << std::endl;
	std::cout << "*                     Vertical Constraint Graph                        *" << std::endl;
	std::cout << "************************************************************************" << std::endl;
	for(int i=0; i<V; i++) {
		if (!adj[i].empty()) {
			std::cout << "Net " << idx2net_level[i]->get_name() << " -> Level: " << levels[i] << " \tAdjacency list: ";
			for(auto iter = adj[i].begin(); iter != adj[i].end(); ++iter) {
				std::cout << idx2net_level[*iter]->get_name() << " ";
			}
			std::cout << "\n" << std::endl;
		}
		else {
			std::cout << "Net " << idx2net_level[i]->get_name() << " -> Level: " << levels[i] << std::endl;
		}
	}
}

// NOTE: Method for getting vertices count
void Graph::printTransposedGraph() {
	// Print graph
	std::cout << "************************************************************************" << std::endl;
	std::cout << "*                         Transposed Graph                             *" << std::endl;
	std::cout << "************************************************************************" << std::endl;
	for(int i=0; i<V; i++) {
		if (!trans_adj[i].empty()) {
			std::cout << "Net " << idx2net_level[i]->get_name() << " -> Level: " << levels[i] << " \tAdjacency list: ";
			for(auto iter = trans_adj[i].begin(); iter != trans_adj[i].end(); ++iter) {
				std::cout << idx2net_level[*iter]->get_name() << " ";
			}
			std::cout << "\n" << std::endl;
		}
		else {
			std::cout << "Net " << idx2net_level[i]->get_name() << " -> Level: " << levels[i] << std::endl;
		}
	}
}

