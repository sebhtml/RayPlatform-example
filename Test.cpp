/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#include "Test.h"

Test::Test(){
	m_doneA=false;
	m_doneB=false;
	m_doneC=false;
}

void Test::registerPlugin(ComputeCore*core){

	/** register the plugin with the core **/

	PluginHandle plugin=core->allocatePluginHandle();
	core->beginPluginRegistration(plugin);
	core->setPluginName(plugin,"Test");

	m_adapter_RAY_MASTER_MODE_STEP_A.setObject(this);
	core->allocateMasterModeHandle(plugin,RAY_MASTER_MODE_STEP_A);
	core->setMasterModeObjectHandler(plugin,RAY_MASTER_MODE_STEP_A,&m_adapter_RAY_MASTER_MODE_STEP_A);

	m_adapter_RAY_MASTER_MODE_STEP_B.setObject(this);
	core->allocateMasterModeHandle(plugin,RAY_MASTER_MODE_STEP_B);
	core->setMasterModeObjectHandler(plugin,RAY_MASTER_MODE_STEP_B,&m_adapter_RAY_MASTER_MODE_STEP_B);

	m_adapter_RAY_MASTER_MODE_STEP_C.setObject(this);
	core->allocateMasterModeHandle(plugin,RAY_MASTER_MODE_STEP_C);
	core->setMasterModeObjectHandler(plugin,RAY_MASTER_MODE_STEP_C,&m_adapter_RAY_MASTER_MODE_STEP_C);

	m_adapter_RAY_SLAVE_MODE_STEP_A.setObject(this);
	core->allocateSlaveModeHandle(plugin,RAY_SLAVE_MODE_STEP_A);
	core->setSlaveModeObjectHandler(plugin,RAY_SLAVE_MODE_STEP_A,&m_adapter_RAY_SLAVE_MODE_STEP_A);

	m_adapter_RAY_SLAVE_MODE_STEP_B.setObject(this);
	core->allocateSlaveModeHandle(plugin,RAY_SLAVE_MODE_STEP_B);
	core->setSlaveModeObjectHandler(plugin,RAY_SLAVE_MODE_STEP_B,&m_adapter_RAY_SLAVE_MODE_STEP_B);

	m_adapter_RAY_SLAVE_MODE_STEP_C.setObject(this);
	core->allocateSlaveModeHandle(plugin,RAY_SLAVE_MODE_STEP_C);
	core->setSlaveModeObjectHandler(plugin,RAY_SLAVE_MODE_STEP_C,&m_adapter_RAY_SLAVE_MODE_STEP_C);

	m_adapter_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL.setObject(this);
	core->allocateMessageTagHandle(plugin,RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL);
	core->setMessageTagObjectHandler(plugin,RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL,&m_adapter_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL);

	core->endPluginRegistration(plugin);

	m_core=core;
}

void Test::call_RAY_MASTER_MODE_STEP_A(){
	if(m_doneA==false){
		m_doneA=true;
		cout<<"Rank "<<m_core->getMessagesHandler()->getRank()<<" call_RAY_MASTER_MODE_STEP_A"<<endl;

		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();
	}
}

void Test::call_RAY_MASTER_MODE_STEP_B(){
	if(m_doneB==false){
		m_doneB=true;
		cout<<"Rank "<<MASTER_RANK<<" call_RAY_MASTER_MODE_STEP_B"<<endl;
		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();
	}
}

void Test::call_RAY_MASTER_MODE_STEP_C(){
	if(m_doneC==false){
		m_doneC=true;
		cout<<"Rank "<<MASTER_RANK<<" call_RAY_MASTER_MODE_STEP_C"<<endl;
		m_core->getSwitchMan()->openMasterMode(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
	}else if(m_core->getSwitchMan()->allRanksAreReady()){
		m_core->getSwitchMan()->closeMasterMode();
	}
}

void Test::call_RAY_SLAVE_MODE_STEP_A(){
	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_RAY_SLAVE_MODE_STEP_A"<<endl;

	m_core->getSwitchMan()->closeSlaveModeLocally(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
}

void Test::call_RAY_SLAVE_MODE_STEP_B(){
	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_RAY_SLAVE_MODE_STEP_B"<<endl;

	m_core->getSwitchMan()->closeSlaveModeLocally(m_core->getOutbox(),m_core->getMessagesHandler()->getRank());
}

void Test::call_RAY_SLAVE_MODE_STEP_C(){

	cout<<"I am "<<m_core->getMessagesHandler()->getRank()<<" doing call_RAY_SLAVE_MODE_STEP_C, now I die"<<endl;

	m_core->stop(); // stop the main loop
	cout<<"This is over "<<endl;
}

void Test::call_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL(Message*message){
	cout<<message->getSource()<<" completed something."<<endl;
	m_core->getSwitchMan()->closeSlaveMode(message->getSource());
}

