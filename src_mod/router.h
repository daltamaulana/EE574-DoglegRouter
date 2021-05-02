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
			// NOTE: Change the loop to std::find_if
			for(i=m_nets.begin();i!=m_nets.end();++i){
				if( (*i)->get_name() == name ) {
					found = true;
					break;
				}
			}
			// Add net if net is not found on net list
			if(!found)  { 
				//std::cout << this << "not found: " << std::endl;
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
			
			/****************************** START ***** */
			route_impl();
			/**************************************** */

			//assert( m_nets.size() == m_routed_num );
			std::cout << " Missed " << m_nets.size() - m_routed_num << " nets" << std::endl;
			m_is_done = true;
		}
		// NOTE: Method for sorting top and bottom track terminals based on its column
		void sort_route_terms() {
			// NOTE: Debug function
			// Terminals before sorting
			std::cout << "Top terminals before sorting: \t";
			for (auto term:top_terms) {
				std::cout << term->col() << "\t";
			}
			std::cout << "\n" << std::endl;

			// Sort top terminals
			std::sort(top_terms.begin(), top_terms.end(), [](ZTerm* terms_a, ZTerm* terms_b) {
				return (terms_a->col() < terms_b->col());
			});

			// NOTE: Debug function
			// Terminals after sorting
			std::cout << "Top terminals after sorting: \t";
			for (auto term:top_terms) {
				std::cout << term->col() << "\t";
			}
			std::cout << "\n" << std::endl;

			// NOTE: Debug function
			// Terminals before sorting
			std::cout << "Bottom terminals before sorting: \t";
			for (auto term:bottom_terms) {
				std::cout << term->col() << "\t";
			}
			std::cout << "\n" << std::endl;

			// Sort bottom terminals
			std::sort(bottom_terms.begin(), bottom_terms.end(), [](ZTerm* terms_a, ZTerm* terms_b) {
				return (terms_a->col() < terms_b->col());
			});

			// NOTE: Debug function
			// Terminals before sorting
			std::cout << "Bottom terminals after sorting: \t";
			for (auto term:bottom_terms) {
				std::cout << term->col() << "\t";
			}
			std::cout << "\n" << std::endl;
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
		// Method for creating vertical constraint graph
		void create_vcg() {
			m_graph = new Graph(get_nets().size());
			// construct VCG (please refer to 'graph.h' and 'graph.cpp')
		}

    public:
		// Declare method
		// Method for routing nets
		virtual void route_impl() {
			// Declare local variable
			unsigned int c_track = 1;

			// NOTE: Test sorting
			sort_route_terms();

			// // Create nets vertical constraint graph
			// create_vcg();
			// // Check graph cyclic property
			// if ( m_graph->isCyclic() ) { 
			// 	// You have to implement breaking multi-terminal nets ( re-construct VCG )
			// } 
			
			// // Loop through all nets
			// while( ! is_done() ) {
			// 	std::vector<ZNet*> nets = m_graph->get_top_nets(); //  get left vertices on VCG
			// 	std::cout << "********************************** have " << nets.size() << " TOP nets to route" << std::endl;

			// 	// you must sort 'nets' by increasing order of position (from left)

			// 	if( ! nets.size() ) break;

			// 	// assign nets on current track

			// 	c_track++;
			// }
		}
};



#endif
