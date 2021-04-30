////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                   //
////////////////////////////////////////////////////////////////////////////////////
#include "router.h"
#include "connectivity.h"

////////////////////////////////////////////////////////////////////////////////////
//                               Define Function                                  //
////////////////////////////////////////////////////////////////////////////////////
// Function for generating test case
void example(ZChannelRouter* router) {
    // Example 1
    ZNet* a = new ZNet("A");
        a->add_term(0,ZUpperTerm);
        a->add_term(2,ZUpperTerm);
            
    ZNet* b = new ZNet("B");
        b->add_term(1,ZUpperTerm);
        b->add_term(0,ZLowerTerm);
        
    ZNet* c = new ZNet("C");
        c->add_term(3,ZUpperTerm);
        c->add_term(1,ZLowerTerm);
        c->add_term(2,ZLowerTerm);

    router->add_net_to_route(a);
    router->add_net_to_route(b);
    router->add_net_to_route(c);

	// Example 2
	/*
    ZNet* a = new ZNet("A");
        a->add_term(1,ZUpperTerm);
        a->add_term(3,ZUpperTerm);

    ZNet* b = new ZNet("B");
        b->add_term(4,ZUpperTerm);
        b->add_term(5,ZLowerTerm);

    ZNet* c = new ZNet("C");
        c->add_term(5,ZUpperTerm);
        c->add_term(1,ZLowerTerm);

    ZNet* d = new ZNet("D");
        d->add_term(3,ZLowerTerm);
        d->add_term(6,ZLowerTerm);

    ZNet* e = new ZNet("E");
        e->add_term(6,ZUpperTerm);
        e->add_term(2,ZLowerTerm);

    ZNet* f = new ZNet("F");
        f->add_term(2,ZUpperTerm);
        f->add_term(0,ZLowerTerm);

    router->add_net_to_route(a);
    router->add_net_to_route(b);
    router->add_net_to_route(c);
    router->add_net_to_route(d);
    router->add_net_to_route(e);
    router->add_net_to_route(f);
	*/

	// Example 3
	/*
    ZNet* a = new ZNet("A");
        a->add_term(0,ZUpperTerm);
        a->add_term(1,ZUpperTerm);

    ZNet* b = new ZNet("B");
        b->add_term(2,ZUpperTerm);
        b->add_term(3,ZUpperTerm);
        b->add_term(1,ZLowerTerm);

    ZNet* c = new ZNet("C");
        c->add_term(3,ZLowerTerm);
        c->add_term(4,ZLowerTerm);

    router->add_net_to_route(a);
    router->add_net_to_route(b);
    router->add_net_to_route(c);
	*/
}
