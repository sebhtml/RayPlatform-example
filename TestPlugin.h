/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#ifndef _TestPlugin_h
#define _TestPlugin_h

#include <RayPlatform/core/ComputeCore.h>

__DeclarePlugin(TestPlugin);

__DeclareMasterModeAdapter(TestPlugin,MY_TEST_MASTER_MODE_STEP_A);
__DeclareMasterModeAdapter(TestPlugin,MY_TEST_MASTER_MODE_STEP_B);
__DeclareMasterModeAdapter(TestPlugin,MY_TEST_MASTER_MODE_STEP_C);

__DeclareSlaveModeAdapter(TestPlugin,MY_TEST_SLAVE_MODE_STEP_A);
__DeclareSlaveModeAdapter(TestPlugin,MY_TEST_SLAVE_MODE_STEP_B);
__DeclareSlaveModeAdapter(TestPlugin,MY_TEST_SLAVE_MODE_STEP_C);

__DeclareMessageTagAdapter(TestPlugin,MY_TEST_MPI_TAG_STOP_AND_DIE);
__DeclareMessageTagAdapter(TestPlugin,MY_TEST_MPI_TAG_TIME_BOMB);

/**
 * The plugin TestPlugin
 * **/
class TestPlugin:  public CorePlugin{

	__AddAdapter(TestPlugin,MY_TEST_MASTER_MODE_STEP_A);
	__AddAdapter(TestPlugin,MY_TEST_MASTER_MODE_STEP_B);
	__AddAdapter(TestPlugin,MY_TEST_MASTER_MODE_STEP_C);

	__AddAdapter(TestPlugin,MY_TEST_SLAVE_MODE_STEP_A);
	__AddAdapter(TestPlugin,MY_TEST_SLAVE_MODE_STEP_B);
	__AddAdapter(TestPlugin,MY_TEST_SLAVE_MODE_STEP_C);

	__AddAdapter(TestPlugin,MY_TEST_MPI_TAG_STOP_AND_DIE);
	__AddAdapter(TestPlugin,MY_TEST_MPI_TAG_TIME_BOMB);

/**
 * A list of master modes
 */
	MasterMode MY_TEST_MASTER_MODE_STEP_A;
	MasterMode MY_TEST_MASTER_MODE_STEP_B;
	MasterMode MY_TEST_MASTER_MODE_STEP_C;

/** slave modes **/
	SlaveMode MY_TEST_SLAVE_MODE_STEP_A;
	SlaveMode MY_TEST_SLAVE_MODE_STEP_B;
	SlaveMode MY_TEST_SLAVE_MODE_STEP_C;
	SlaveMode RAY_SLAVE_MODE_DO_NOTHING;


	MessageTag MY_TEST_MPI_TAG_START_STEP_A;
	MessageTag MY_TEST_MPI_TAG_START_STEP_B;
	MessageTag MY_TEST_MPI_TAG_START_STEP_C;
	
	MessageTag MY_TEST_MPI_TAG_TIME_BOMB;
	MessageTag MY_TEST_MPI_TAG_STOP_AND_DIE;

	ComputeCore*m_core;

/** states for progression **/
	bool m_doneA;
	bool m_doneB;
	bool m_doneC;
public:

	TestPlugin();

/** callbacks for master modes **/
	void call_MY_TEST_MASTER_MODE_STEP_A();
	void call_MY_TEST_MASTER_MODE_STEP_B();
	void call_MY_TEST_MASTER_MODE_STEP_C();

/** callbacks for slave modes **/
	void call_MY_TEST_SLAVE_MODE_STEP_A();
	void call_MY_TEST_SLAVE_MODE_STEP_B();
	void call_MY_TEST_SLAVE_MODE_STEP_C();

	void call_MY_TEST_MPI_TAG_TIME_BOMB(Message*message);
	void call_MY_TEST_MPI_TAG_STOP_AND_DIE(Message*message);

/** the following two methods are required by the interface CorePlugin **/

/** register the plugin with the core **/
	void registerPlugin(ComputeCore*core);

/** resolve symbols not owned by the current plugin **/
	void resolveSymbols(ComputeCore*core);
};

#endif
