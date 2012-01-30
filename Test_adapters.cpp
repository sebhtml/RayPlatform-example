/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

/** implementation of the adapters for the plugin Test **/

#include "Test_adapters.h"
#include "Test.h"

void Adapter_RAY_MASTER_MODE_STEP_A::setObject(Test*object){
	m_object=object;
}

void Adapter_RAY_MASTER_MODE_STEP_A::call(){
	m_object->call_RAY_MASTER_MODE_STEP_A();
}

void Adapter_RAY_MASTER_MODE_STEP_B::setObject(Test*object){
	m_object=object;
}

void Adapter_RAY_MASTER_MODE_STEP_B::call(){
	m_object->call_RAY_MASTER_MODE_STEP_B();
}

void Adapter_RAY_MASTER_MODE_STEP_C::setObject(Test*object){
	m_object=object;
}

void Adapter_RAY_MASTER_MODE_STEP_C::call(){
	m_object->call_RAY_MASTER_MODE_STEP_C();
}

void Adapter_RAY_SLAVE_MODE_STEP_A::setObject(Test*object){
	m_object=object;
}

void Adapter_RAY_SLAVE_MODE_STEP_A::call(){
	m_object->call_RAY_SLAVE_MODE_STEP_A();
}

void Adapter_RAY_SLAVE_MODE_STEP_B::setObject(Test*object){
	m_object=object;
}

void Adapter_RAY_SLAVE_MODE_STEP_B::call(){
	m_object->call_RAY_SLAVE_MODE_STEP_B();
}

void Adapter_RAY_SLAVE_MODE_STEP_C::setObject(Test*object){
	m_object=object;
}

void Adapter_RAY_SLAVE_MODE_STEP_C::call(){
	m_object->call_RAY_SLAVE_MODE_STEP_C();
}


