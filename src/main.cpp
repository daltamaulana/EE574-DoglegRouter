//////////////////////////////////////////////////////////////////////////////////////
//                               Import Library                                     //
//////////////////////////////////////////////////////////////////////////////////////
// User created library
#include "router.h"
#include "example.h"

//////////////////////////////////////////////////////////////////////////////////////
//                               Main Function                                      //
//////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char* args[] ) {
	// Declare new router object
	ZChannelRouter* router = new ZLeftEdgeChannelRouter;
    
	// Open example file
	string fileName = string(args[1]);
	// Add terminals to router object
	example(router);
	// example(router, fileName);
	
	// Routing process 	
	router->route();
    
	// Print routing result
    router->print_result();

	// Return value
	return 0;
}
