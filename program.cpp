/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#include <core/ComputeCore.h>
#include "Test.h"
using namespace std;

int main(int argc,char**argv){

/** build the ComputeCore
 * the ComputeCore is the kernel of 
 * a RayPlatform-based parallel application
 *
 * it manages a lot of stuff for the programmer.
 * **/
	ComputeCore core;
	core.constructor(&argc,&argv);

/**
 * the only thing you can do to alter your application
 * is to register plugins
 *
 * RayPlatform plugins are similar
 * to Linux modules.
 **/
	Test testPlugin;

	core.registerPlugin(&testPlugin);

	// more plugins can be registered !

/**
 * Then the core is started
 */
	core.run();

/**
 * When the core returns
 * we destroy it safely 
 */
	core.destructor();

	return 0;
}
