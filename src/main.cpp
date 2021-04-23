#include "router.h"

#include "example.h"

int main( int argc, char* args[] )
{
	
	ZChannelRouter* router = new ZLeftEdgeChannelRouter;
    example(router);
	
	//routing 	
	router->route();
    
	// Please print your output (routing result) with the format as mentioned in README
        
	return 0;
}
