#ifndef objects_h
#define objects_h

//////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                     //
//////////////////////////////////////////////////////////////////////////////////////
// User created library
#include "connectivity.h"
// Standard library
#include <cassert>
#include <set>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////
//                    Declare Constant and Custom Data Types                        //
//////////////////////////////////////////////////////////////////////////////////////
const int CHANNEL_MAX=30; // Maximum number of tracks (including top and bottom term)
enum ZTermType { ZInputTerm, ZOutputTerm }; // Terminal type
enum ZTermOrientation { ZLowerTerm = 0, ZUpperTerm = CHANNEL_MAX  }; // Term position

//////////////////////////////////////////////////////////////////////////////////////
//                       Declare Class and Its Attributes                           //
//////////////////////////////////////////////////////////////////////////////////////
class ZNet;

class ZTerm {
	public:
		// Declare attributes
		std::string m_name; // Terminal name
		unsigned int m_colnum; // Terminal position (column)
		ZTermOrientation m_orient; // Terminal position (top or bottom)
		ZNet* m_owner_net; // Terminal owner (net)

		// Declare constructor
		ZTerm(unsigned int col,ZTermOrientation orient,ZNet* net):m_colnum(col),m_orient(orient),m_owner_net(net) {
			
		}

		ZTerm(const char* name, unsigned int col,ZTermOrientation orient):m_name(name),m_colnum(col),m_orient(orient),m_owner_net(0) {
			
		}

		ZTerm(unsigned int col,ZTermOrientation orient,ZNet* net,const char* name):m_colnum(col),m_orient(orient),m_owner_net(net),m_name(name) {
			
		}
		
		// Declare methods
		// Return owner net of the terminal
		ZNet* net() { 
			assert(m_owner_net); 
			return  m_owner_net; 
		}     
		// Getter method for terminal column
		virtual unsigned int col() { 
			return m_colnum; 
		}
		// Getter method for terminal orientation
		virtual ZTermOrientation row() { 
			return m_orient; 
		}

		virtual unsigned int row1() { 
			return !row()?0:(CHANNEL_MAX+1); 
		}
		// Getter method for terminal name
		virtual std::string name() { 
			return m_name; 
		}
		// Setter method for terminal name
		void set_name(const std::string& s) { 
			m_name = s;
		}
};

#endif
