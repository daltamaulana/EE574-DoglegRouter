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
    // // Example 1
    // ZNet* a = new ZNet("A");
    //     a->add_term(0,ZUpperTerm);
    //     a->add_term(2,ZUpperTerm);
            
    // ZNet* b = new ZNet("B");
    //     b->add_term(1,ZUpperTerm);
    //     b->add_term(0,ZLowerTerm);
        
    // ZNet* c = new ZNet("C");
    //     c->add_term(3,ZUpperTerm);
    //     c->add_term(1,ZLowerTerm);
    //     c->add_term(2,ZLowerTerm);

    // router->add_net_to_route(a);
    // router->add_net_to_route(b);
    // router->add_net_to_route(c);

	// // Example 2
    // ZNet* a = new ZNet("A");
    //     a->add_term(1,ZUpperTerm);
    //     a->add_term(3,ZUpperTerm);

    // ZNet* b = new ZNet("B");
    //     b->add_term(4,ZUpperTerm);
    //     b->add_term(5,ZLowerTerm);

    // ZNet* c = new ZNet("C");
    //     c->add_term(5,ZUpperTerm);
    //     c->add_term(1,ZLowerTerm);

    // ZNet* d = new ZNet("D");
    //     d->add_term(3,ZLowerTerm);
    //     d->add_term(6,ZLowerTerm);

    // ZNet* e = new ZNet("E");
    //     e->add_term(6,ZUpperTerm);
    //     e->add_term(2,ZLowerTerm);

    // ZNet* f = new ZNet("F");
    //     f->add_term(2,ZUpperTerm);
    //     f->add_term(0,ZLowerTerm);

    // router->add_net_to_route(a);
    // router->add_net_to_route(b);
    // router->add_net_to_route(c);
    // router->add_net_to_route(d);
    // router->add_net_to_route(e);
    // router->add_net_to_route(f);

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

    // // Example 4
    // ZNet* a = new ZNet("A");
    //     a->add_term(4,ZUpperTerm);
    //     a->add_term(5,ZLowerTerm);
            
    // ZNet* b = new ZNet("B");
    //     b->add_term(1,ZUpperTerm);
    //     b->add_term(3,ZUpperTerm);
        
    // ZNet* c = new ZNet("C");
    //     c->add_term(1,ZLowerTerm);
    //     c->add_term(5,ZUpperTerm);

    // ZNet* d = new ZNet("D");
    //     d->add_term(0,ZLowerTerm);
    //     d->add_term(2,ZUpperTerm);

    // ZNet* e = new ZNet("E");
    //     e->add_term(2,ZLowerTerm);
    //     e->add_term(6,ZUpperTerm);

    // ZNet* f = new ZNet("F");
    //     f->add_term(3,ZLowerTerm);
    //     f->add_term(6,ZLowerTerm);

    // router->add_net_to_route(a);
    // router->add_net_to_route(b);
    // router->add_net_to_route(c);
    // router->add_net_to_route(d);
    // router->add_net_to_route(e);
    // router->add_net_to_route(f);

    // // Example 5
    // ZNet* a = new ZNet("A");
    //     a->add_term(4,ZUpperTerm);
    //     a->add_term(5,ZUpperTerm);
            
    // ZNet* b = new ZNet("B");
    //     b->add_term(0,ZLowerTerm);
    //     b->add_term(1,ZLowerTerm);
        
    // ZNet* c = new ZNet("C");
    //     c->add_term(0,ZUpperTerm);
    //     c->add_term(2,ZLowerTerm);
    //     c->add_term(4,ZLowerTerm);

    // ZNet* d = new ZNet("D");
    //     d->add_term(1,ZUpperTerm);
    //     d->add_term(3,ZUpperTerm);
    //     d->add_term(5,ZLowerTerm);

    // router->add_net_to_route(a);
    // router->add_net_to_route(b);
    // router->add_net_to_route(c);
    // router->add_net_to_route(d);

    // // Example 6
    // ZNet* a = new ZNet("A");
    //     a->add_term(1,ZUpperTerm);
    //     a->add_term(4,ZUpperTerm);
            
    // ZNet* b = new ZNet("B");
    //     b->add_term(0,ZLowerTerm);
    //     b->add_term(5,ZLowerTerm);
        
    // ZNet* c = new ZNet("C");
    //     c->add_term(1,ZLowerTerm);
    //     c->add_term(3,ZLowerTerm);

    // ZNet* d = new ZNet("D");
    //     d->add_term(2,ZUpperTerm);
    //     d->add_term(8,ZUpperTerm);

    // ZNet* e = new ZNet("E");
    //     e->add_term(2,ZLowerTerm);
    //     e->add_term(3,ZUpperTerm);
    //     e->add_term(4,ZLowerTerm);

    // ZNet* f = new ZNet("F");
    //     f->add_term(5,ZUpperTerm);
    //     f->add_term(6,ZLowerTerm);

    // ZNet* g = new ZNet("G");
    //     g->add_term(6,ZUpperTerm);
    //     g->add_term(10,ZLowerTerm);

    // ZNet* h = new ZNet("H");
    //     h->add_term(7,ZLowerTerm);
    //     h->add_term(9,ZLowerTerm);

    // ZNet* i = new ZNet("I");
    //     i->add_term(8,ZLowerTerm);
    //     i->add_term(9,ZUpperTerm);
    //     i->add_term(11,ZLowerTerm);
    
    // ZNet* j = new ZNet("J");
    //     j->add_term(10,ZUpperTerm);
    //     j->add_term(11,ZUpperTerm);

    // router->add_net_to_route(a);
    // router->add_net_to_route(b);
    // router->add_net_to_route(c);
    // router->add_net_to_route(d);
    // router->add_net_to_route(e);
    // router->add_net_to_route(f);
    // router->add_net_to_route(g);
    // router->add_net_to_route(h);
    // router->add_net_to_route(i);
    // router->add_net_to_route(j);

    // // Example 7
    // ZNet* a = new ZNet("A");
    //     a->add_term(0,ZUpperTerm);
    //     a->add_term(2,ZLowerTerm);
            
    // ZNet* b = new ZNet("B");
    //     b->add_term(0,ZLowerTerm);
    //     b->add_term(1,ZUpperTerm);
    //     b->add_term(2,ZUpperTerm);

    // router->add_net_to_route(a);
    // router->add_net_to_route(b);

    // Example 8
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
}
