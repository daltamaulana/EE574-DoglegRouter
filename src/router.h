#ifndef router_h
#define router_h

//////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                     //
//////////////////////////////////////////////////////////////////////////////////////
// User created library
#include "graph.h"
#include "connectivity.h"
// Standard library
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

//////////////////////////////////////////////////////////////////////////////////////
//                       Declare Class and Its Attributes                           //
//////////////////////////////////////////////////////////////////////////////////////
// Channel router class
class ZChannelRouter {
	public:
		// Declare attributes
		bool m_is_done; // Flag for routing status
		bool m_terms_stored; // Flag for marking whether terminals are stored in router class
		unsigned int maxtracks; // Number of max tracks in channel
		unsigned int m_routed_num; // Number of routed nets
		unsigned int m_max_used_track; // Number of current max used tracks

		std::list<ZNet*> m_nets; // List of nets
		std::vector<ZTerm*> top_terms; // Vector for storing top terminals
		std::vector<ZTerm*> bottom_terms; // Vector for storing bottom terminals
		std::vector<int> m_nets_in_col; // Vector for storing number of nets in each columns
		std::map<ZNet*,unsigned int> m_net2track; // Store net to track map
		std::map<unsigned int,std::vector<ZNet*> > m_track2nets; // Store track to net map

	public:
		// Declare methods
		// Class constructor
        ZChannelRouter():m_terms_stored(false),maxtracks(CHANNEL_MAX),m_routed_num(0),m_max_used_track(0),m_is_done(false) {

        }
		// Getter method for max tracks value
		unsigned get_maxtracks() {
			//std::cout << maxtracks << std::endl;
			return maxtracks;
		}
		// Setter method for max tracks value
		unsigned set_maxtracks(unsigned int t) {
			maxtracks = t;
			return maxtracks;
		}
		// Getter method for routing status
		bool is_done() {
			return m_is_done;
		}
		// Getter method for list of nets
        std::list<ZNet*> get_nets() {
          return m_nets;
        }
		// Getter method for net track
		unsigned int get_net_track(ZNet* N) {
			// Assert nets
          	assert(N);
	  		// Return value for undefined net
	  		if (N->get_name().empty()) {
				return 9999999;
			} else {
          		return m_net2track[N];
			}
        }
		// Setter method for store terms value
		void terms_willbe_stored() {
			m_terms_stored = true; 
		}

		// Method for adding net to net list
		ZNet* get_or_add_net(ZNet* n) {
			// Declare iterator
			std::list<ZNet*>::iterator i;
			// Check for net in the net list	  
			if (std::find(m_nets.begin(), m_nets.end(), n) == m_nets.end()) {
				// Add net to net list if net is new
				m_nets.push_back(n);
			}
			// Return net	
			return n;
		}

        // Method for adding named net to netlist
		ZNet* get_or_create_net_by_name(const std::string& name) {
			// Declare local variable
			bool found = false;
			// Declare iterator
			std::list<ZNet*>::iterator i;

			// Search for net in net list
			// Change the loop to std::find_if
			for(i=m_nets.begin();i!=m_nets.end();++i){
				if( (*i)->get_name() == name ) {
					found = true;
					break;
				}
			}
			// Add net if net is not found on net list
			if(!found)  { 
				ZNet* net = new ZNet(name); 
				m_nets.push_back(net);
				return net;
			}

			// Return net
			return *i;
		}

		// Method for adding terminal to net
		void add_term_to_net(ZNet* N, unsigned int col, ZTermOrientation o) {
            // Add terminal to net
			ZTerm* t = N->add_term(col,o);
            // Store terminal to router terminal list
			store_term(t);
        }

		// Method for storing terminals to router terminal list
		void store_terms() {
			// Loop through nets
			for(std::list<ZNet*>::iterator i=m_nets.begin(); i!=m_nets.end(); ++i) {
				// Store terminals
				store_net_terms(*i);
			}
		}

		// Method for adding net to net list
		void add_net_to_route(ZNet* n) {
			// Assert net
			assert(n);
			ZNet* m = get_or_add_net(n);
			assert( m == n && "Confused..." );
		}

		// Virtual method for checking net conflicts
		virtual bool has_confliscts(ZNet* n1, ZNet* n2) {
			// Get first net closest and furthest terminal
			unsigned int a1 = n1->get_closest_term()->col();
			unsigned int b1 = n1->get_farest_term()->col();
			// Get second net closest and furthest terminal
			unsigned int a2 = n2->get_closest_term()->col();
			unsigned int b2 = n2->get_farest_term()->col();

			// Conflict checking
			// Vertical constraint
			if ( a1 == a2 || b1 == b2 ) return true;
			if ( a1 == b2 || b1 == a2 ) return true;
			if ( b1 == a1 || b2 == a2 ) return true;
			// Horizontal constraint
			if ( a1 > a2 ) return ( b2 >= a1 );
			if ( a2 > a1 ) return ( a2 <= b1 ); 
			// Default value
			return true;
		}

		// Method for checking whether net can be assigned on track or not
		bool check_can_be_assigned_on_track(ZNet* n, unsigned t) {
			// Declare iterator
			std::vector<ZNet*>::iterator i;
			// Get net on track info
			std::vector<ZNet*> routed_nets = m_track2nets[t];

			// Case when there is no net on the track
			if (!routed_nets.size()) {
				return true;
			} 
			// Case when there are nets on the track
			// Loop through nets
			for(i=routed_nets.begin();i!=routed_nets.end();++i ) {
				// Check for conflict
				if (has_confliscts(n,*i)) {
					return false;
				} 
			}
			// Default return value
			return true;
		}

		// Method for assigning net to track
		void assign_net_to_track(ZNet* N, unsigned int t) { 
			m_routed_num++; 
			m_net2track[N] = t; 
			m_track2nets[t].push_back(N);

			if ( t > m_max_used_track ) {
				m_max_used_track = t;
			}
		}

		// Method for assigning net to track
		bool try_to_assign(ZNet* net, unsigned track) {
			if (check_can_be_assigned_on_track(net,track)) {
				// Assign net to track
				assign_net_to_track(net,track); 
				return true;
			}
			// Default return value
			return false; 
		}

		// Virtual method which implements routing process
        virtual void route_impl() = 0; 

		// Method for routing nets
		void route() {
			std::cout << " Nets to route: " << m_nets.size() << std::endl;
			m_is_done = false;

			if ( !m_terms_stored )
				store_terms();
			
			route_impl();

			std::cout << " Missed " << m_nets.size() - m_routed_num << " nets" << std::endl;
			m_is_done = true;
		}

		// NOTE: Method for sorting top and bottom track terminals based on its column
		void sort_route_terms() {
			// Sort top terminals
			std::sort(top_terms.begin(), top_terms.end(), [](ZTerm* terms_a, ZTerm* terms_b) {
				return (terms_a->col() < terms_b->col());
			});

			// Sort bottom terminals
			std::sort(bottom_terms.begin(), bottom_terms.end(), [](ZTerm* terms_a, ZTerm* terms_b) {
				return (terms_a->col() < terms_b->col());
			});
		}

		// NOTE: Method for sorting nets in channel
		void sort_route_nets() {
			// Sort terminals in net
			m_nets.sort([](ZNet* net_a, ZNet* net_b) {
				// Declare temp variables
				auto a_closest_term = net_a->get_closest_term();
				auto b_closest_term = net_b->get_closest_term();
				auto a_orientation = a_closest_term->row();
				auto b_orientation = b_closest_term->row();

				// Sort criteria
				if (a_closest_term->col() < b_closest_term->col()) {
					return true;
				} else if (a_closest_term->col() > b_closest_term->col()) {
					return false;
				} else {
					if ((a_orientation == ZUpperTerm) && (b_orientation == ZLowerTerm)) {
						return true;
					} else if ((a_orientation == ZLowerTerm) && (b_orientation == ZUpperTerm)) {
						return false;
					} else {
						return true;
					}
				}
			});
		}

		// NOTE: Method for splitting nets
		void split_net(ZNet* n) {
			// Declare local variable
			int idx = 0;
			int terms_count = n->terms_count();
			std::string parent_name = n->get_name();
			std::string child_name;
			std::list<ZTerm*> net_terms;

			// Sort terminal inside net
			n->sort_net_terms();
			// Get net terminals
			net_terms = n->get_terms();
			
			// Declare iterator
			std::list<ZTerm*>::iterator last_iter = net_terms.end();
			// Set last net to second last terminal in net
			--last_iter;

			// Split net process
			for (std::list<ZTerm*>::iterator iter = net_terms.begin(); iter != last_iter; ++iter) {
				// Generate child name
				child_name = std::to_string(idx);
				// Create new child net
				ZNet* a = new ZNet(parent_name, parent_name+child_name);
					a->add_term((*iter)->col(), (*iter)->row());
					a->add_term((*std::next(iter))->col(), (*std::next(iter))->row());
				// Add new net to router net list
				this->add_net_to_route(a);
				// Increment index
				idx++;
			}
		}

  	private:
		// Method for storing terminals
		void store_term(ZTerm* t) { 
			if ( t->row() == ZLowerTerm )
				bottom_terms.push_back(t);
			else
				top_terms.push_back(t);
		}

		// Method for storing net terminals
		void store_net_terms (ZNet* n) {
			// Get list of terminals in the net
			std::list<ZTerm*> terms = n->get_terms();
			// Iterate through each terminal
			for(std::list<ZTerm*>::iterator i = terms.begin(); i != terms.end(); ++i) {
				store_term(*i);
			}
		}
};

// Left edge channel router class (inherit channel router class)
class ZLeftEdgeChannelRouter: public ZChannelRouter {
	private:
		// Declare attribute
		Graph* m_graph; // Vertical constraint graph

		// Declare method
		// Method for creating zone representation (horizontal constraint graph)
		void create_zone_repr(){
			// Declare local variable
			int max_col = 0;
			int max_nets = 0;
			int closest_col = 0;
			int furthest_col = 0;

			// Get max number of column in channel
			if (top_terms.back()->col() >= bottom_terms.back()->col()) {
				max_col = top_terms.back()->col();
			} else {
				max_col = bottom_terms.back()->col();
			}

			// Initialize m_nets_in_col vector
			m_nets_in_col.resize(max_col+1);
			for(int i=0;i<max_col;i++)  {
				m_nets_in_col[i] = 0;  		
			}

			// Iterate through all nets in channel
			for(auto iter = m_nets.begin(); iter != m_nets.end(); ++iter) {
				closest_col = (*iter)->get_closest_term()->col();
				furthest_col = (*iter)->get_farest_term()->col();
				std::cout << "Max col: " << max_col << "\tClosest col: " << closest_col << "\tFurthest col: " << furthest_col << std::endl;
				// Update m_nets_in_col value
				for(int i=closest_col; i<=furthest_col; i++) {
					m_nets_in_col[i] += 1;
				}
			}

			// Get maximum number of nets in column
			max_nets = *std::max_element(m_nets_in_col.begin(), m_nets_in_col.end());
			
			// Update maxtracks value
			set_maxtracks(max_nets);
		}

		// Method for creating vertical constraint graph
void create_vcg() {
	// Declare new graph object
	m_graph = new Graph(get_nets().size());
	
	// Declare iterator for top terminal
	std::vector<ZTerm*>::iterator top_iter;

	// Iterate through top terminal
	for(top_iter=top_terms.begin(); top_iter != top_terms.end(); ++top_iter) {
		// Declare iterator for bottom terminal (Search terminal with same column)
		auto bottom_iter = std::find_if(bottom_terms.begin(), bottom_terms.end(), [top_iter](ZTerm* term) {
			return (*top_iter)->col() == term->col();
		});
		// Iterate through bottom terminal (searching terminal with same column)
		// Found column with top and bottom terminals
		if (bottom_iter != bottom_terms.end()) {
			// Check whether top and bottom terminal are on the same net
			if ((*bottom_iter)->m_owner_net->get_name() == (*top_iter)->m_owner_net->get_name()) {
				// Add vertex to graph
				m_graph->addVertex((*top_iter)->net());
			} else {
				// Add new vertices and edge to graph
				m_graph->addEdge((*top_iter)->net(), (*bottom_iter)->net());
			}
		} else {
			// Add vertex to graph
			m_graph->addVertex((*top_iter)->net());
		}
	}
}

    public:
		// Declare method
		// Method for routing nets
		virtual void route_impl() {
			// Declare local variable
			unsigned int c_track = 1;

			// Sort terminals
			sort_route_terms();
			// Sort nets
			sort_route_nets();
			// Create zone representation (HCG)
			create_zone_repr();
			// Create nets vertical constraint graph (VCG)
			create_vcg();

			// Check graph cyclic property
			if (m_graph->isCyclic()) { 
				// You have to implement breaking multi-terminal nets ( re-construct VCG )
				std::cout << "Graph is cyclic, reconstructing VCG!" << std::endl;
				// Iterate through net list
				for(auto iter = m_nets.begin(); iter != m_nets.end();) {
					// Check number of terminals in net
					if ((*iter)->terms_count() > 2) {
						// Split net
						split_net(*iter);
						// Remove all terminals related to parent net
						auto top_iter = std::remove_if(top_terms.begin(), top_terms.end(), [iter](ZTerm* term) {
							return (*iter) == term->net();
						});
						top_terms.erase(top_iter, top_terms.end());
						auto bottom_iter = std::remove_if(bottom_terms.begin(), bottom_terms.end(), [iter](ZTerm* term) {
							return (*iter) == term->net();
						});
						bottom_terms.erase(bottom_iter, bottom_terms.end());
						// Remove parent net from net list
						iter = m_nets.erase(iter);
					} else {
						// Next element
						++iter;
					}
				}

				// Clear terminals
				top_terms.clear();
				bottom_terms.clear();

				// Reassign terminal
				store_terms();
				// Sort terminals
				sort_route_terms();
				// Sort nets
				sort_route_nets();
				// Create zone representation (HCG)
				create_zone_repr();
				// Create nets vertical constraint graph (VCG)
				create_vcg();
			} else {
				std::cout << "Graph isn't cyclic!" << std::endl;
			}
			
			// Loop through all nets
			while(!is_done()) {
				std::vector<ZNet*> nets = m_graph->get_top_nets(); //  get left vertices on VCG
				std::cout << "************************************************************************" << std::endl;
				std::cout << "*             Routing info: router have " << nets.size() << " TOP nets to route            *" << std::endl;
				std::cout << "************************************************************************" << std::endl;

				// you must sort 'nets' by increasing order of position (from left)
				if (!nets.size()) {
					break;
				} else {
					// assign nets on current track
					// Iterate throughh top nets
					for (auto iter = nets.begin(); iter != nets.end(); ++iter) {
						if (try_to_assign((*iter), c_track)) {
							std::cout << "Routing net: " << (*iter)->get_name() << std::endl;
							m_graph->printGraph();
							m_graph->transposeGraph();
							m_graph->printTransposedGraph();
							m_graph->decrease_adj_level(*iter);
							m_graph->removeVertex(*iter);
						} else {
							std::cout << "Routing net: " << (*iter)->get_name() << std::endl;
							std::cout << "Need to set net " << (*iter)->get_name() << " to route" << std::endl;
							m_graph->set_need2route(*iter);
						}
					}
					// Increase track level
					c_track++;
				}

				// NOTE: Print graph
				m_graph->printGraph();
			}

			// Print max number of tracks
			std::cout << "Max number of tracks: " << get_maxtracks() << std::endl;

			// Print tracks
			for(auto iter = m_nets.begin(); iter != m_nets.end(); ++iter) {
				std::cout << "Net name: " << (*iter)->get_name() << " Track: " << get_net_track(*iter) << std::endl;
			}
		}
};



#endif
