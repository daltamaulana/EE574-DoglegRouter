#ifndef connectivity_h
#define connectivity_h

//////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                     //
//////////////////////////////////////////////////////////////////////////////////////
// User created library
#include "objects.h"
// Standard library
#include <cassert>
#include <string>
#include <list>

//////////////////////////////////////////////////////////////////////////////////////
//                       Declare Class and Its Attributes                           //
//////////////////////////////////////////////////////////////////////////////////////
class ZNet {
    private:
		// Declare class attributes
		std::string m_name; // Net name
		bool is_first_term; // Flag to marks first terminal in net
		ZTerm* m_farest_term; // Pointer to furthest terminal (rightmost)
		ZTerm* m_closest_term; // Pointer to closest terminal (leftmost)
		std::list<ZTerm*> terms; // List of terminals in net
		unsigned int m_terms_count; // Number of terminals in net

    public:
		// Declare constructor
		ZNet (const std::string& str ):m_terms_count(0),m_name(str) { 
			m_farest_term = 0;
			m_closest_term = 0;
			is_first_term = true;
		}

		// Declare methods
		// Getter method for net name
		std::string get_name() { 
			return m_name; 
		}
		// Getter method for terminal counts
		unsigned int terms_count() {
			return m_terms_count;
		}
		// Getter method for getting closest terminal
		ZTerm* get_closest_term() {
			assert(m_closest_term);
			return m_closest_term;
		}
		// Getter method for getting furthest terminal
		ZTerm* get_farest_term() { 
			assert(m_farest_term);
			return m_farest_term;
		}
		// Getter method for getting list of all terminals in net
		std::list<ZTerm*> get_terms() {
			return terms;
		}
		// Method for creating new terminal in nets
		ZTerm* add_term(unsigned int c, ZTermOrientation o, const char* n = "?") {
			//std::cout << "Nearest:" << m_closest_term<< " Farest:" << m_farest_term << std::endl;

			ZTerm* t = new ZTerm(c,o,this,n);
			//terms.push_back(t);
			//m_terms_count++;

			return add_term_base(t);
		}
		// Method for adding terminal to net
		ZTerm* add_term_base(ZTerm* t) {
			terms.push_back(t);
			m_terms_count++;
			unsigned int c = t->col();

			if ( is_first_term ) {
				m_closest_term = t;
				m_farest_term = t;
				is_first_term = false;
				return t;
			}

			if ( m_closest_term && c < m_closest_term->col()) m_closest_term = t;
			if ( m_farest_term && c > m_farest_term->col()) m_farest_term = t;

			return t;
		}
};

#endif
