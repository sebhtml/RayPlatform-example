/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#include "Test.h"

Test::Test(){
	m_doneA=false;
	m_doneB=false;
	m_doneC=false;
}

void Test::call_MY_TEST_MASTER_MODE_STEP_A(){
	if(m_doneA==false){
		m_doneA=true;
		cout<<"Rank "<<m_core->getMessagesHandler()->getRank()<<" call_MY_TEST_MASTER_MODE_STEP_A"<<endl;

		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();
	}
}

void Test::call_MY_TEST_MASTER_MODE_STEP_B(){
	if(m_doneB==false){
		m_doneB=true;
		cout<<"Rank "<<MASTER_RANK<<" call_MY_TEST_MASTER_MODE_STEP_B"<<endl;
		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();
	}
}

void Test::call_MY_TEST_MASTER_MODE_STEP_C(){
	if(m_doneC==false){
		m_doneC=true;
		cout<<"Rank "<<MASTER_RANK<<" call_MY_TEST_MASTER_MODE_STEP_C"<<endl;
		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();

		
	}
}

void Test::call_MY_TEST_SLAVE_MODE_STEP_A(){
	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_MY_TEST_SLAVE_MODE_STEP_A"<<endl;

	m_core->getSwitchMan()->closeSlaveModeLocally(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
}

void Test::call_MY_TEST_SLAVE_MODE_STEP_B(){
	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_MY_TEST_SLAVE_MODE_STEP_B"<<endl;

	m_core->getSwitchMan()->closeSlaveModeLocally(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
}

void Test::call_MY_TEST_SLAVE_MODE_STEP_C(){

	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_MY_TEST_SLAVE_MODE_STEP_C, now I die"<<endl;

	m_core->stop(); // stop the main loop
	cout<<"This is over "<<endl;
}

void Test::registerPlugin(ComputeCore*core){

	cout<<"Registering plugin"<<endl;

	/** register the m_plugin with the core **/

	m_plugin=core->allocatePluginHandle();

	core->setPluginName(m_plugin,"Test");

	// for each master mode, we allocate a handle 
	// after that, we register a handler for it
	//
	// allocateMasterModeHandle takes 2 arguments
	//  - the plugin handle
	//  - the desired value for the requested master mode handle

	MY_TEST_MASTER_MODE_STEP_A=core->allocateMasterModeHandle(m_plugin,MY_TEST_MASTER_MODE_STEP_A);
	m_adapter_MY_TEST_MASTER_MODE_STEP_A.setObject(this);
	core->setMasterModeObjectHandler(m_plugin,MY_TEST_MASTER_MODE_STEP_A,&m_adapter_MY_TEST_MASTER_MODE_STEP_A);
	core->setMasterModeSymbol(m_plugin,MY_TEST_MASTER_MODE_STEP_A,"MY_TEST_MASTER_MODE_STEP_A");

	MY_TEST_MASTER_MODE_STEP_B=core->allocateMasterModeHandle(m_plugin,MY_TEST_MASTER_MODE_STEP_B);
	m_adapter_MY_TEST_MASTER_MODE_STEP_B.setObject(this);
	core->setMasterModeObjectHandler(m_plugin,MY_TEST_MASTER_MODE_STEP_B,&m_adapter_MY_TEST_MASTER_MODE_STEP_B);
	core->setMasterModeSymbol(m_plugin,MY_TEST_MASTER_MODE_STEP_B,"MY_TEST_MASTER_MODE_STEP_B");

	MY_TEST_MASTER_MODE_STEP_C=core->allocateMasterModeHandle(m_plugin,MY_TEST_MASTER_MODE_STEP_C);
	m_adapter_MY_TEST_MASTER_MODE_STEP_C.setObject(this);
	core->setMasterModeObjectHandler(m_plugin,MY_TEST_MASTER_MODE_STEP_C,&m_adapter_MY_TEST_MASTER_MODE_STEP_C);
	core->setMasterModeSymbol(m_plugin,MY_TEST_MASTER_MODE_STEP_C,"MY_TEST_MASTER_MODE_STEP_C");

	// for each slave mode, we allocate a handle 
	// after that, we register a handler for it

	MY_TEST_SLAVE_MODE_STEP_A=core->allocateSlaveModeHandle(m_plugin,MY_TEST_SLAVE_MODE_STEP_A);
	m_adapter_MY_TEST_SLAVE_MODE_STEP_A.setObject(this);
	core->setSlaveModeObjectHandler(m_plugin,MY_TEST_SLAVE_MODE_STEP_A,&m_adapter_MY_TEST_SLAVE_MODE_STEP_A);
	core->setSlaveModeSymbol(m_plugin,MY_TEST_SLAVE_MODE_STEP_A,"MY_TEST_SLAVE_MODE_STEP_A");

	MY_TEST_SLAVE_MODE_STEP_B=core->allocateSlaveModeHandle(m_plugin,MY_TEST_SLAVE_MODE_STEP_B);
	m_adapter_MY_TEST_SLAVE_MODE_STEP_B.setObject(this);
	core->setSlaveModeObjectHandler(m_plugin,MY_TEST_SLAVE_MODE_STEP_B,&m_adapter_MY_TEST_SLAVE_MODE_STEP_B);
	core->setSlaveModeSymbol(m_plugin,MY_TEST_SLAVE_MODE_STEP_B,"MY_TEST_SLAVE_MODE_STEP_B");

	MY_TEST_SLAVE_MODE_STEP_C=core->allocateSlaveModeHandle(m_plugin,MY_TEST_SLAVE_MODE_STEP_C);
	m_adapter_MY_TEST_SLAVE_MODE_STEP_C.setObject(this);
	core->setSlaveModeObjectHandler(m_plugin,MY_TEST_SLAVE_MODE_STEP_C,&m_adapter_MY_TEST_SLAVE_MODE_STEP_C);
	core->setSlaveModeSymbol(m_plugin,MY_TEST_SLAVE_MODE_STEP_C,"MY_TEST_SLAVE_MODE_STEP_C");

	MY_TEST_MPI_TAG_START_STEP_A=core->allocateMessageTagHandle(m_plugin,MY_TEST_MPI_TAG_START_STEP_A);
	MY_TEST_MPI_TAG_START_STEP_B=core->allocateMessageTagHandle(m_plugin,MY_TEST_MPI_TAG_START_STEP_B);
	MY_TEST_MPI_TAG_START_STEP_C=core->allocateMessageTagHandle(m_plugin,MY_TEST_MPI_TAG_START_STEP_C);

	// now, we register the order of the master modes
	
	core->setMasterModeNextMasterMode(m_plugin,MY_TEST_MASTER_MODE_STEP_A,MY_TEST_MASTER_MODE_STEP_B);
	core->setMasterModeNextMasterMode(m_plugin,MY_TEST_MASTER_MODE_STEP_B,MY_TEST_MASTER_MODE_STEP_C);

	
	core->setMasterModeToMessageTagSwitch(m_plugin,MY_TEST_MASTER_MODE_STEP_A,MY_TEST_MPI_TAG_START_STEP_A);
	core->setMasterModeToMessageTagSwitch(m_plugin,MY_TEST_MASTER_MODE_STEP_B,MY_TEST_MPI_TAG_START_STEP_B);
	core->setMasterModeToMessageTagSwitch(m_plugin,MY_TEST_MASTER_MODE_STEP_C,MY_TEST_MPI_TAG_START_STEP_C);

	core->setMessageTagToSlaveModeSwitch(m_plugin,MY_TEST_MPI_TAG_START_STEP_A,MY_TEST_SLAVE_MODE_STEP_A);
	core->setMessageTagToSlaveModeSwitch(m_plugin,MY_TEST_MPI_TAG_START_STEP_B,MY_TEST_SLAVE_MODE_STEP_B);
	core->setMessageTagToSlaveModeSwitch(m_plugin,MY_TEST_MPI_TAG_START_STEP_C,MY_TEST_SLAVE_MODE_STEP_C);

	// finally, we define an entry point
	core->setFirstMasterMode(m_plugin,MY_TEST_MASTER_MODE_STEP_A);

	m_core=core;
}

void Test::resolveSymbols(ComputeCore*core){

	cout<<"Resolving symbols"<<endl;
	// here, we resolve symbols owned by other m_plugins
	// but needed by the current m_plugin
	// obviously, this is not needed here because
	// we only have one m_plugin
	
	MY_TEST_SLAVE_MODE_STEP_A=core->getSlaveModeFromSymbol(m_plugin,"MY_TEST_SLAVE_MODE_STEP_A");
}


