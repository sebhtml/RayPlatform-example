/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

/**
 * this file contain adaptors for the plugin Test
 **/

#ifndef _Test_adapters_h
#define _Test_adapters_h

#include <handlers/MasterModeHandler.h>
#include <handlers/SlaveModeHandler.h>
#include <handlers/MessageTagHandler.h>

class Test;

class Adapter_MY_TEST_MASTER_MODE_STEP_A: public MasterModeHandler{
	Test*m_object;
public:
	void setObject(Test*object);
	void call();
};

class Adapter_MY_TEST_MASTER_MODE_STEP_B: public MasterModeHandler{
	Test*m_object;
public:
	void setObject(Test*object);
	void call();
};

class Adapter_MY_TEST_MASTER_MODE_STEP_C: public MasterModeHandler{
	Test*m_object;
public:
	void setObject(Test*object);
	void call();
};

class Adapter_MY_TEST_SLAVE_MODE_STEP_A: public SlaveModeHandler{
	Test*m_object;
public:
	void setObject(Test*object);
	void call();
};

class Adapter_MY_TEST_SLAVE_MODE_STEP_B: public SlaveModeHandler{
	Test*m_object;
public:
	void setObject(Test*object);
	void call();
};

class Adapter_MY_TEST_SLAVE_MODE_STEP_C: public SlaveModeHandler{
	Test*m_object;
public:
	void setObject(Test*object);
	void call();
};

#endif
