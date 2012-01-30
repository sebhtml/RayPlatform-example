/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

/** implementation of the adapters for the plugin Test **/

#include "Test_adapters.h"
#include "Test.h"

void Adapter_MY_TEST_MASTER_MODE_STEP_A::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_MASTER_MODE_STEP_A::call(){
	m_object->call_MY_TEST_MASTER_MODE_STEP_A();
}

void Adapter_MY_TEST_MASTER_MODE_STEP_B::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_MASTER_MODE_STEP_B::call(){
	m_object->call_MY_TEST_MASTER_MODE_STEP_B();
}

void Adapter_MY_TEST_MASTER_MODE_STEP_C::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_MASTER_MODE_STEP_C::call(){
	m_object->call_MY_TEST_MASTER_MODE_STEP_C();
}

void Adapter_MY_TEST_SLAVE_MODE_STEP_A::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_SLAVE_MODE_STEP_A::call(){
	m_object->call_MY_TEST_SLAVE_MODE_STEP_A();
}

void Adapter_MY_TEST_SLAVE_MODE_STEP_B::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_SLAVE_MODE_STEP_B::call(){
	m_object->call_MY_TEST_SLAVE_MODE_STEP_B();
}

void Adapter_MY_TEST_SLAVE_MODE_STEP_C::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_SLAVE_MODE_STEP_C::call(){
	m_object->call_MY_TEST_SLAVE_MODE_STEP_C();
}

void Adapter_MY_TEST_MPI_TAG_STOP_AND_DIE::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_MPI_TAG_STOP_AND_DIE::call(Message*m){
	m_object->call_MY_TEST_MPI_TAG_STOP_AND_DIE(m);
}

void Adapter_MY_TEST_MPI_TAG_TIME_BOMB::setObject(Test*object){
	m_object=object;
}

void Adapter_MY_TEST_MPI_TAG_TIME_BOMB::call(Message*m){
	m_object->call_MY_TEST_MPI_TAG_TIME_BOMB(m);
}


