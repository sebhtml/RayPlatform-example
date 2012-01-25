/** all the necessary code is in this file for clarity **/
/** how the blocks come together is described in scripting/ */
/** author: Sébastien Boisvert **/

#include <core/ComputeCore.h>
#include <iostream>
using namespace std;

class Test: public SlaveModeHandler, public MasterModeHandler, public MessageTagHandler, public CorePlugin{
	ComputeCore m_computeCore;

	bool m_doneA;
	bool m_doneB;
	bool m_doneC;
public:
	Test(int*argc,char***argv){
		m_computeCore.constructor(argc,argv);

		m_computeCore.registerPlugin(this);// register the only plugin

		m_doneA=false;
		m_doneB=false;
		m_doneC=false;
	}

	// for the CorePlugin interface
	void registerPlugin(ComputeCore*core){

		core->setMasterModeObjectHandler(RAY_MASTER_MODE_STEP_A, this);
		core->setMasterModeObjectHandler(RAY_MASTER_MODE_STEP_B, this);
		core->setMasterModeObjectHandler(RAY_MASTER_MODE_STEP_C, this);

		core->setSlaveModeObjectHandler(RAY_SLAVE_MODE_STEP_A, this);
		core->setSlaveModeObjectHandler(RAY_SLAVE_MODE_STEP_B, this);
		core->setSlaveModeObjectHandler(RAY_SLAVE_MODE_STEP_C, this);

		core->setMessageTagObjectHandler(RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL, this);
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

		m_computeCore.stop(); // stop the main loop
		cout<<"This is over "<<endl;
	}

	void call_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL(Message*message){
		cout<<message->getSource()<<" completed something."<<endl;
		m_computeCore.getSwitchMan()->closeSlaveMode(message->getSource());
	}

	void run(){
		m_computeCore.run();
		m_computeCore.destructor();
	}
};

int main(int argc,char**argv){
	Test test(&argc,&argv);
	test.run();

	return EXIT_SUCCESS;
}
