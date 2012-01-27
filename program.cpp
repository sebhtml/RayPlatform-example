/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#include <core/ComputeCore.h>
#include <iostream>
#include "Test.h"
using namespace std;

/** 
 * this method utilises macros to read files in scripting/
 * to configure the switchman
 * */
void configureSwitchMan(SwitchMan*switchMan){
	#ifdef ASSERT
	assert(switchMan!=NULL);
	#endif

	// configure the switch man
	//
	// this is where steps can be added or removed.

	vector<MasterMode> steps;

	#define ITEM(x) \
	steps.push_back(x);

	#include <master_mode_order.txt>

	#undef ITEM

	for(int i=0;i<(int)steps.size();i++){
		#ifdef ASSERT
		assert(i<(int)steps.size());
		#endif

		switchMan->addMasterMode(steps[i]);
	}

	for(int i=0;i<(int)steps.size()-1;i++){
		#ifdef ASSERT
		assert(i+1<(int)steps.size());
		#endif

		switchMan->addNextMasterMode(steps[i],steps[i+1]);
	}

	#define ITEM(mpiTag,slaveMode) \
	switchMan->addSlaveSwitch(mpiTag,slaveMode);
	
	#include <slave_switches.txt>

	#undef ITEM

	#define ITEM(masterMode,mpiTag) \
	switchMan->addMasterSwitch(masterMode,mpiTag);
	
	#include <master_switches.txt>

	#undef ITEM

	if(switchMan->getRank()==MASTER_RANK){
		MasterMode mode=switchMan->getMasterModeOrder()->at(0);
		switchMan->setMasterMode(mode);
	}
}



int main(int argc,char**argv){

	ComputeCore core;

	core.constructor(&argc,&argv);

	configureSwitchMan(core.getSwitchMan());

	Test testPlugin;

	core.registerPlugin(&testPlugin);

	core.run();

	core.destructor();

	return 0;
}
