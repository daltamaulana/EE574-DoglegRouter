#ifndef objects_h
#define objects_h

#include "connectivity.h"

#include <cassert>
#include <set>
#include <iostream>

const int CHANNEL_MAX=30;
enum ZTermOrientation { ZLowerTerm = CHANNEL_MAX, ZUpperTerm = 0  };
enum ZTermType { ZInputTerm, ZOutputTerm };

class ZTerm
{
	public:
		//ZTerm(ZTerm&)
		ZTerm(unsigned int col,ZTermOrientation orient,ZNet* net):m_colnum(col),m_orient(orient),m_owner_net(net) {
			//std::cout << m_
		}

		ZTerm(unsigned int col,ZTermOrientation orient,ZNet* net,const char* name):m_colnum(col),m_orient(orient),m_owner_net(net),m_name(name) {
			//std::cout << m_
		}

		ZTerm(const char* name, unsigned int col,ZTermOrientation orient):m_name(name),m_colnum(col),m_orient(orient),m_owner_net(0) {
			//std::cout << m_
		}

		ZNet* net() { assert(m_owner_net); return  m_owner_net; }     

		virtual unsigned int col() { return m_colnum; }
		virtual unsigned int row() { return m_orient; }

		virtual unsigned int row1() { return !row()?0:(CHANNEL_MAX+1); }

		virtual std::string name() { return m_name; }

		void set_name(const std::string& s) { 
			// std::cout << " ZTERM: " << m_name << " -> " << s << std::endl;
			m_name = s;

		}

		unsigned int m_colnum;
		ZTermOrientation m_orient;
		ZNet* m_owner_net;
		std::string m_name;
};


#endif
