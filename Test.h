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
	Adapter_RAY_MASTER_MODE_STEP_A m_adapter_RAY_MASTER_MODE_STEP_A;
	Adapter_RAY_MASTER_MODE_STEP_B m_adapter_RAY_MASTER_MODE_STEP_B;
	Adapter_RAY_MASTER_MODE_STEP_C m_adapter_RAY_MASTER_MODE_STEP_C;

	Adapter_RAY_SLAVE_MODE_STEP_A m_adapter_RAY_SLAVE_MODE_STEP_A;
	Adapter_RAY_SLAVE_MODE_STEP_B m_adapter_RAY_SLAVE_MODE_STEP_B;
	Adapter_RAY_SLAVE_MODE_STEP_C m_adapter_RAY_SLAVE_MODE_STEP_C;

	Adapter_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL m_adapter_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL;

	ComputeCore*m_core;

	bool m_doneA;
	bool m_doneB;
	bool m_doneC;
public:

	Test();
	void registerPlugin(ComputeCore*core);
	void call_RAY_MASTER_MODE_STEP_A();
	void call_RAY_MASTER_MODE_STEP_B();
	void call_RAY_MASTER_MODE_STEP_C();
	void call_RAY_SLAVE_MODE_STEP_A();
	void call_RAY_SLAVE_MODE_STEP_B();
	void call_RAY_SLAVE_MODE_STEP_C();
	void call_RAY_MPI_TAG_SWITCHMAN_COMPLETION_SIGNAL(Message*message);
};

#endif
