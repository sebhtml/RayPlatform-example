/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

#ifndef _Test_h
#define _Test_h

#include "Test_adapters.h"
#include <core/ComputeCore.h>

/**
 * The plugin Test
 * **/
class Test:  public CorePlugin{

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

/** adapters for master modes **/
	Adapter_MY_TEST_MASTER_MODE_STEP_A m_adapter_MY_TEST_MASTER_MODE_STEP_A;
	Adapter_MY_TEST_MASTER_MODE_STEP_B m_adapter_MY_TEST_MASTER_MODE_STEP_B;
	Adapter_MY_TEST_MASTER_MODE_STEP_C m_adapter_MY_TEST_MASTER_MODE_STEP_C;

/** adapters for slave modes **/
	Adapter_MY_TEST_SLAVE_MODE_STEP_A m_adapter_MY_TEST_SLAVE_MODE_STEP_A;
	Adapter_MY_TEST_SLAVE_MODE_STEP_B m_adapter_MY_TEST_SLAVE_MODE_STEP_B;
	Adapter_MY_TEST_SLAVE_MODE_STEP_C m_adapter_MY_TEST_SLAVE_MODE_STEP_C;

	MessageTag MY_TEST_MPI_TAG_START_STEP_A;
	MessageTag MY_TEST_MPI_TAG_START_STEP_B;
	MessageTag MY_TEST_MPI_TAG_START_STEP_C;

	ComputeCore*m_core;

/** states for progression **/
	bool m_doneA;
	bool m_doneB;
	bool m_doneC;
public:

	Test();

/** callbacks for master modes **/
	void call_MY_TEST_MASTER_MODE_STEP_A();
	void call_MY_TEST_MASTER_MODE_STEP_B();
	void call_MY_TEST_MASTER_MODE_STEP_C();

/** callbacks for slave modes **/
	void call_MY_TEST_SLAVE_MODE_STEP_A();
	void call_MY_TEST_SLAVE_MODE_STEP_B();
	void call_MY_TEST_SLAVE_MODE_STEP_C();

/** the following two methods are required by the interface CorePlugin **/

/** register the plugin with the core **/
	void registerPlugin(ComputeCore*core);

/** resolve symbols not owned by the current plugin **/
	void resolveSymbols(ComputeCore*core);
};

#endif
