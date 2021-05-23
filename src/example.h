#include "router.h"
#include "connectivity.h"
#include <fstream>
#include <map> 

void example(ZChannelRouter* router) {
  
	// /* example 1 */
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

    // Example 7
    ZNet* a = new ZNet("A");
        a->add_term(0,ZUpperTerm);
        a->add_term(2,ZLowerTerm);
            
    ZNet* b = new ZNet("B");
        b->add_term(0,ZLowerTerm);
        b->add_term(1,ZUpperTerm);
        b->add_term(2,ZUpperTerm);

    router->add_net_to_route(a);
    router->add_net_to_route(b);

	/* example 2 */
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

	/* exmaple 3*/

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

void example(ZChannelRouter* router, string fileName){

	ifstream ifs;
	ifs.open( fileName );
	//unordered_map<string, ZNet*> name2net;
	map<string, ZNet*> name2net;
	while( !ifs.eof() ){
		string tmp;

		getline( ifs, tmp );
		if( tmp == "" ){
			break;
		}

		istringstream iss;
		iss.str( tmp );
		string tmpStr;
		iss >> tmpStr;
		string netname = tmpStr;
		//cout << netname << endl;
		if( name2net.find( netname ) == name2net.end() ){
			ZNet* net = new ZNet(netname);
			name2net[netname] = net;
		}
		iss >> tmpStr ;
		unsigned int col = atoi(tmpStr.c_str());
		//cout << col << endl;
		iss >> tmpStr;
		if( tmpStr == "U" ){
			name2net[netname]->add_term(col, ZUpperTerm);
			cout << "Add term " << col << " upper to net " << netname << endl;
		} else if (tmpStr == "L"){
			name2net[netname]->add_term(col, ZLowerTerm);
			cout << "Add term " << col << " lower to net " << netname << endl;
		} else {
			cout << "The location of terminal is wrong!!" << endl;
			exit(1);
		}
	}
	ifs.close();

	map<string, ZNet*>::iterator it = name2net.begin();
	
	while( it != name2net.end() ){
		cout << "Add " << it->first << " to route" << endl;
		router->add_net_to_route( it->second );
		it++;
	}
}
