#ifndef connectivity_h
#define connectivity_h

#include "objects.h"

#include <cassert>
#include <string>
#include <list>


class ZNet 
{
    
    public:
		ZNet (const std::string& str ):m_terms_count(0),m_name(str) { 
			m_farest_term = 0;
			m_closest_term = 0;
			is_first_term = true;

		}

		ZTerm* add_term(unsigned int c, ZTermOrientation o, const char* n = "?") {
			//std::cout << "Nearest:" << m_closest_term<< " Farest:" << m_farest_term << std::endl;

			ZTerm* t = new ZTerm(c,o,this,n);
			//terms.push_back(t);
			//m_terms_count++;

			return add_term_base(t);
		}

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


		std::list<ZTerm*> get_terms() {
			return terms;
		}

		ZTerm* get_closest_term() {
			assert(m_closest_term);
			return m_closest_term;

		}

		ZTerm* get_farest_term() { 
			assert(m_farest_term);
			return m_farest_term;
		}

		std::string get_name() { return m_name; }

		unsigned int terms_count() {
			return m_terms_count;
		}

    private:
         
		  ZTerm* m_farest_term;
		  ZTerm* m_closest_term;
		  bool is_first_term;

		  std::list<ZTerm*> terms;
		  unsigned int m_terms_count;

		  std::string m_name;
};





#endif
