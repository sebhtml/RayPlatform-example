/** all the necessary code is in this file **/
/** how the blocks come together is described in scripting/ */


#include <core/ComputeCore.h>
#include <iostream>
#include <stdlib.h>
#include <memory/malloc_types.h>
#include <core/OperatingSystem.h> 
#include <scripting/ScriptEngine.h>
using namespace std;

class Test: public SlaveModeHandler, public MasterModeHandler, public MessageTagHandler{
	ComputeCore m_computeCore;

	bool m_doneA;
	bool m_doneB;
	bool m_doneC;
public:
	Test(int*argc,char***argv){
		m_computeCore.constructor(argc,argv);

		// move in platform
		m_computeCore.getSwitchMan()->setMasterMode(RAY_MASTER_MODE_DO_NOTHING); 
		m_computeCore.getSwitchMan()->setSlaveMode(RAY_SLAVE_MODE_DO_NOTHING);

		if(m_computeCore.getMessagesHandler()->getRank()==MASTER_RANK){
			m_computeCore.getSwitchMan()->setMasterMode(RAY_MASTER_MODE_STEP_A);
		}

		m_computeCore.setMasterModeObjectHandler(RAY_MASTER_MODE_STEP_A, this);
		m_computeCore.setMasterModeObjectHandler(RAY_MASTER_MODE_STEP_B, this);
		m_computeCore.setMasterModeObjectHandler(RAY_MASTER_MODE_STEP_C, this);

		m_computeCore.setSlaveModeObjectHandler(RAY_SLAVE_MODE_STEP_A, this);
		m_computeCore.setSlaveModeObjectHandler(RAY_SLAVE_MODE_STEP_B, this);
		m_computeCore.setSlaveModeObjectHandler(RAY_SLAVE_MODE_STEP_C, this);

		m_computeCore.setMessageTagObjectHandler(RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL, this);

		m_doneA=false;
		m_doneB=false;
		m_doneC=false;

		m_computeCore.getInbox()->constructor(m_computeCore.getMaximumNumberOfAllocatedInboxMessages(),RAY_MALLOC_TYPE_INBOX_VECTOR,false);
		m_computeCore.getOutbox()->constructor(m_computeCore.getMaximumNumberOfAllocatedOutboxMessages(),RAY_MALLOC_TYPE_OUTBOX_VECTOR,false);

		ScriptEngine engine;
		m_computeCore.getSwitchMan()->constructor(m_computeCore.getMessagesHandler()->getSize());

		engine.configureSwitchMan(m_computeCore.getSwitchMan());
	}

	void call_RAY_MASTER_MODE_STEP_A(){
		if(m_doneA==false){
			m_doneA=true;
			cout<<"Rank "<<m_computeCore.getMessagesHandler()->getRank()<<" call_RAY_MASTER_MODE_STEP_A"<<endl;

			m_computeCore.getSwitchMan()->openMasterMode(m_computeCore.getOutbox(),m_computeCore.getMessagesHandler()->getRank());
		}else if(m_computeCore.getSwitchMan()->allRanksAreReady()){
			m_computeCore.getSwitchMan()->closeMasterMode();
		}
	}

	void call_RAY_MASTER_MODE_STEP_B(){
		if(m_doneB==false){
			m_doneB=true;
			cout<<"Rank "<<MASTER_RANK<<" call_RAY_MASTER_MODE_STEP_B"<<endl;
			m_computeCore.getSwitchMan()->openMasterMode(m_computeCore.getOutbox(),m_computeCore.getMessagesHandler()->getRank());
		}else if(m_computeCore.getSwitchMan()->allRanksAreReady()){
			m_computeCore.getSwitchMan()->closeMasterMode();
		}
	}

	void call_RAY_MASTER_MODE_STEP_C(){
		if(m_doneC==false){
			m_doneC=true;
			cout<<"Rank "<<MASTER_RANK<<" call_RAY_MASTER_MODE_STEP_C"<<endl;
			m_computeCore.getSwitchMan()->openMasterMode(m_computeCore.getOutbox(),m_computeCore.getMessagesHandler()->getRank());
		}else if(m_computeCore.getSwitchMan()->allRanksAreReady()){
			m_computeCore.getSwitchMan()->closeMasterMode();
		}
	}

	void call_RAY_SLAVE_MODE_STEP_A(){
		cout<<"I am "<<m_computeCore.getMessagesHandler()->getRank()<<" doing call_RAY_SLAVE_MODE_STEP_A"<<endl;

		m_computeCore.getSwitchMan()->closeSlaveModeLocally(m_computeCore.getOutbox(),m_computeCore.getMessagesHandler()->getRank());
	}

	void call_RAY_SLAVE_MODE_STEP_B(){
		cout<<"I am "<<m_computeCore.getMessagesHandler()->getRank()<<" doing call_RAY_SLAVE_MODE_STEP_B"<<endl;

		m_computeCore.getSwitchMan()->closeSlaveModeLocally(m_computeCore.getOutbox(),m_computeCore.getMessagesHandler()->getRank());
	}

	void call_RAY_SLAVE_MODE_STEP_C(){

		cout<<"I am "<<m_computeCore.getMessagesHandler()->getRank()<<" doing call_RAY_SLAVE_MODE_STEP_C, now I die"<<endl;


		bool*life=m_computeCore.getLife();
		*life=false;
		
		cout<<"This is over "<<endl;
	}

	void call_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL(Message*message){
		cout<<message->getSource()<<" completed something."<<endl;
		m_computeCore.getSwitchMan()->closeSlaveMode(message->getSource());
	}

	void run(){
		m_computeCore.run();
	
		m_computeCore.getMessagesHandler()->destructor();
	}
};

int main(int argc,char**argv){

	Test test(&argc,&argv);

	test.run();

	return EXIT_SUCCESS;
}
