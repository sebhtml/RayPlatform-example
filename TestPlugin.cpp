/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#include "TestPlugin.h"

____CreateMasterModeAdapterImplementation(TestPlugin,MY_TEST_MASTER_MODE_STEP_A);
____CreateMasterModeAdapterImplementation(TestPlugin,MY_TEST_MASTER_MODE_STEP_B);
____CreateMasterModeAdapterImplementation(TestPlugin,MY_TEST_MASTER_MODE_STEP_C);

____CreateSlaveModeAdapterImplementation(TestPlugin,MY_TEST_SLAVE_MODE_STEP_A);
____CreateSlaveModeAdapterImplementation(TestPlugin,MY_TEST_SLAVE_MODE_STEP_B);
____CreateSlaveModeAdapterImplementation(TestPlugin,MY_TEST_SLAVE_MODE_STEP_C);

____CreateMessageTagAdapterImplementation(TestPlugin,MY_TEST_MPI_TAG_STOP_AND_DIE);
____CreateMessageTagAdapterImplementation(TestPlugin,MY_TEST_MPI_TAG_TIME_BOMB);



TestPlugin::TestPlugin(){
	m_doneA=false;
	m_doneB=false;
	m_doneC=false;
}

void TestPlugin::call_MY_TEST_MASTER_MODE_STEP_A(){
	if(m_doneA==false){
		m_doneA=true;
		cout<<"Rank "<<m_core->getMessagesHandler()->getRank()<<" call_MY_TEST_MASTER_MODE_STEP_A"<<endl;

		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();
	}
}

void TestPlugin::call_MY_TEST_MASTER_MODE_STEP_B(){
	if(m_doneB==false){
		m_doneB=true;
		cout<<"Rank "<<MASTER_RANK<<" call_MY_TEST_MASTER_MODE_STEP_B"<<endl;
		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();
	}
}

void TestPlugin::call_MY_TEST_MASTER_MODE_STEP_C(){
	if(m_doneC==false){
		m_doneC=true;
		cout<<"Rank "<<MASTER_RANK<<" call_MY_TEST_MASTER_MODE_STEP_C"<<endl;
		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();

		
	}
}

void TestPlugin::call_MY_TEST_SLAVE_MODE_STEP_A(){
	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_MY_TEST_SLAVE_MODE_STEP_A"<<endl;

	m_core->getSwitchMan()->closeSlaveModeLocally(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
}

void TestPlugin::call_MY_TEST_SLAVE_MODE_STEP_B(){
	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_MY_TEST_SLAVE_MODE_STEP_B"<<endl;

	m_core->getSwitchMan()->closeSlaveModeLocally(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
}

void TestPlugin::call_MY_TEST_SLAVE_MODE_STEP_C(){

	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_MY_TEST_SLAVE_MODE_STEP_C, now I die"<<endl;

	cout<<"This is over "<<endl;

	if(m_core->getMessagesHandler()->getRank()==0){
		uint64_t*buffer=(uint64_t*)m_core->getOutboxAllocator()->allocate(1*sizeof(uint64_t));
		buffer[0]=100;

		// compute the next destination
		Rank destination=m_core->getMessagesHandler()->getRank()+1;
		if(destination==m_core->getMessagesHandler()->getSize())
			destination=0;

		Message aMessage(buffer,1,destination,MY_TEST_MPI_TAG_TIME_BOMB,m_core->getMessagesHandler()->getRank());

		// send the bomb to another rank
		m_core->getOutbox()->push_back(aMessage);
	}

	// do nothing now
	m_core->getSwitchMan()->setSlaveMode(RAY_SLAVE_MODE_DO_NOTHING);
}

void TestPlugin::call_MY_TEST_MPI_TAG_TIME_BOMB(Message*message){
	uint64_t*buffer=message->getBuffer();

	if(buffer[0]==0){
		cout<<"The bomb exploded on rank "<<m_core->getMessagesHandler()->getRank()<<" !"<<endl;

		// kill everyone

		m_core->sendEmptyMessageToAll(MY_TEST_MPI_TAG_STOP_AND_DIE);
	}else{
		uint64_t*bufferOut=(uint64_t*)m_core->getOutboxAllocator()->allocate(1*sizeof(uint64_t));
		bufferOut[0]=buffer[0]-1;

		cout<<"Remaining time before the explosion is "<<bufferOut[0]<<" according to rank "<<m_core->getMessagesHandler()->getRank()<<endl;

		// compute the next destination
		Rank destination=m_core->getMessagesHandler()->getRank()+1;
		if(destination==m_core->getMessagesHandler()->getSize())
			destination=0;

		Message aMessage(bufferOut,1,destination,MY_TEST_MPI_TAG_TIME_BOMB,m_core->getMessagesHandler()->getRank());

		// send the bomb to another rank
		m_core->getOutbox()->push_back(aMessage);
	}
}

void TestPlugin::call_MY_TEST_MPI_TAG_STOP_AND_DIE(Message*message){

	cout<<"rank "<<m_core->getMessagesHandler()->getRank()<<" received message MY_TEST_MPI_TAG_STOP_AND_DIE, this kills the batman"<<endl;

	m_core->stop();
}

void TestPlugin::registerPlugin(ComputeCore*core){

	/** register the m_plugin with the core **/

	m_plugin=core->allocatePluginHandle();

	core->setPluginName(m_plugin,"TestPlugin");

	// for each master mode, we allocate a handle 
	// after that, we register a handler for it
	//
	// allocateMasterModeHandle takes 2 arguments
	//  - the plugin handle
	//  - the desired value for the requested master mode handle

	MY_TEST_MASTER_MODE_STEP_A=core->allocateMasterModeHandle(m_plugin);
	m_adapter_MY_TEST_MASTER_MODE_STEP_A.setObject(this);
	core->setMasterModeObjectHandler(m_plugin,MY_TEST_MASTER_MODE_STEP_A,&m_adapter_MY_TEST_MASTER_MODE_STEP_A);
	core->setMasterModeSymbol(m_plugin,MY_TEST_MASTER_MODE_STEP_A,"MY_TEST_MASTER_MODE_STEP_A");

	MY_TEST_MASTER_MODE_STEP_B=core->allocateMasterModeHandle(m_plugin);
	m_adapter_MY_TEST_MASTER_MODE_STEP_B.setObject(this);
	core->setMasterModeObjectHandler(m_plugin,MY_TEST_MASTER_MODE_STEP_B,&m_adapter_MY_TEST_MASTER_MODE_STEP_B);
	core->setMasterModeSymbol(m_plugin,MY_TEST_MASTER_MODE_STEP_B,"MY_TEST_MASTER_MODE_STEP_B");

	MY_TEST_MASTER_MODE_STEP_C=core->allocateMasterModeHandle(m_plugin);
	m_adapter_MY_TEST_MASTER_MODE_STEP_C.setObject(this);
	core->setMasterModeObjectHandler(m_plugin,MY_TEST_MASTER_MODE_STEP_C,&m_adapter_MY_TEST_MASTER_MODE_STEP_C);
	core->setMasterModeSymbol(m_plugin,MY_TEST_MASTER_MODE_STEP_C,"MY_TEST_MASTER_MODE_STEP_C");

	// for each slave mode, we allocate a handle 
	// after that, we register a handler for it

	MY_TEST_SLAVE_MODE_STEP_A=core->allocateSlaveModeHandle(m_plugin);
	m_adapter_MY_TEST_SLAVE_MODE_STEP_A.setObject(this);
	core->setSlaveModeObjectHandler(m_plugin,MY_TEST_SLAVE_MODE_STEP_A,&m_adapter_MY_TEST_SLAVE_MODE_STEP_A);
	core->setSlaveModeSymbol(m_plugin,MY_TEST_SLAVE_MODE_STEP_A,"MY_TEST_SLAVE_MODE_STEP_A");

	MY_TEST_SLAVE_MODE_STEP_B=core->allocateSlaveModeHandle(m_plugin);
	m_adapter_MY_TEST_SLAVE_MODE_STEP_B.setObject(this);
	core->setSlaveModeObjectHandler(m_plugin,MY_TEST_SLAVE_MODE_STEP_B,&m_adapter_MY_TEST_SLAVE_MODE_STEP_B);
	core->setSlaveModeSymbol(m_plugin,MY_TEST_SLAVE_MODE_STEP_B,"MY_TEST_SLAVE_MODE_STEP_B");

	MY_TEST_SLAVE_MODE_STEP_C=core->allocateSlaveModeHandle(m_plugin);
	m_adapter_MY_TEST_SLAVE_MODE_STEP_C.setObject(this);
	core->setSlaveModeObjectHandler(m_plugin,MY_TEST_SLAVE_MODE_STEP_C,&m_adapter_MY_TEST_SLAVE_MODE_STEP_C);
	core->setSlaveModeSymbol(m_plugin,MY_TEST_SLAVE_MODE_STEP_C,"MY_TEST_SLAVE_MODE_STEP_C");

	MY_TEST_MPI_TAG_START_STEP_A=core->allocateMessageTagHandle(m_plugin);
	MY_TEST_MPI_TAG_START_STEP_B=core->allocateMessageTagHandle(m_plugin);
	MY_TEST_MPI_TAG_START_STEP_C=core->allocateMessageTagHandle(m_plugin);

	// now, we register the order of the master modes
	
	core->setMasterModeNextMasterMode(m_plugin,MY_TEST_MASTER_MODE_STEP_A,MY_TEST_MASTER_MODE_STEP_B);
	core->setMasterModeNextMasterMode(m_plugin,MY_TEST_MASTER_MODE_STEP_B,MY_TEST_MASTER_MODE_STEP_C);

	// configure which control message to send given a master mode
	core->setMasterModeToMessageTagSwitch(m_plugin,MY_TEST_MASTER_MODE_STEP_A,MY_TEST_MPI_TAG_START_STEP_A);
	core->setMasterModeToMessageTagSwitch(m_plugin,MY_TEST_MASTER_MODE_STEP_B,MY_TEST_MPI_TAG_START_STEP_B);
	core->setMasterModeToMessageTagSwitch(m_plugin,MY_TEST_MASTER_MODE_STEP_C,MY_TEST_MPI_TAG_START_STEP_C);

	// configure which slave mode to set given a message tag
	core->setMessageTagToSlaveModeSwitch(m_plugin,MY_TEST_MPI_TAG_START_STEP_A,MY_TEST_SLAVE_MODE_STEP_A);
	core->setMessageTagToSlaveModeSwitch(m_plugin,MY_TEST_MPI_TAG_START_STEP_B,MY_TEST_SLAVE_MODE_STEP_B);
	core->setMessageTagToSlaveModeSwitch(m_plugin,MY_TEST_MPI_TAG_START_STEP_C,MY_TEST_SLAVE_MODE_STEP_C);

	// finally, we define an entry point
	core->setFirstMasterMode(m_plugin,MY_TEST_MASTER_MODE_STEP_A);

	m_core=core;

	// configure the two message tags

	MY_TEST_MPI_TAG_TIME_BOMB=core->allocateMessageTagHandle(m_plugin);
	m_adapter_MY_TEST_MPI_TAG_TIME_BOMB.setObject(this);
	core->setMessageTagObjectHandler(m_plugin,MY_TEST_MPI_TAG_TIME_BOMB,&m_adapter_MY_TEST_MPI_TAG_TIME_BOMB);

	MY_TEST_MPI_TAG_STOP_AND_DIE=core->allocateMessageTagHandle(m_plugin);
	m_adapter_MY_TEST_MPI_TAG_STOP_AND_DIE.setObject(this);
	core->setMessageTagObjectHandler(m_plugin,MY_TEST_MPI_TAG_STOP_AND_DIE,&m_adapter_MY_TEST_MPI_TAG_STOP_AND_DIE);

	/* a plugin can share any of its object with other plugins **/
	/** other plugins have to resolve the symbol. **/
	void*object=&m_doneA;
	core->setObjectSymbol(m_plugin,object,"BooleanState");
}

void TestPlugin::resolveSymbols(ComputeCore*core){

	// here, we resolve symbols owned by other m_plugins
	// but needed by the current m_plugin
	// obviously, this is not needed here because
	// we only have one m_plugin
	
	MY_TEST_SLAVE_MODE_STEP_A=core->getSlaveModeFromSymbol(m_plugin,"MY_TEST_SLAVE_MODE_STEP_A");

	// this slave mode is registered somewhere in RayPlatform
	RAY_SLAVE_MODE_DO_NOTHING=core->getSlaveModeFromSymbol(m_plugin,"RAY_SLAVE_MODE_DO_NOTHING");

	bool*test=(bool*) core->getObjectFromSymbol(m_plugin,"BooleanState");
}


