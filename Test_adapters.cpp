/** this example is in the public domain **/
/** author: Sébastien Boisvert **/

/** implementation of the adapters for the plugin Test **/

#include "Test_adapters.h"
#include "Test.h"

____CreateMasterModeAdapterImplementation(Test,MY_TEST_MASTER_MODE_STEP_A);
____CreateMasterModeAdapterImplementation(Test,MY_TEST_MASTER_MODE_STEP_B);
____CreateMasterModeAdapterImplementation(Test,MY_TEST_MASTER_MODE_STEP_C);

____CreateSlaveModeAdapterImplementation(Test,MY_TEST_SLAVE_MODE_STEP_A);
____CreateSlaveModeAdapterImplementation(Test,MY_TEST_SLAVE_MODE_STEP_B);
____CreateSlaveModeAdapterImplementation(Test,MY_TEST_SLAVE_MODE_STEP_C);

____CreateMessageTagAdapterImplementation(Test,MY_TEST_MPI_TAG_STOP_AND_DIE);
____CreateMessageTagAdapterImplementation(Test,MY_TEST_MPI_TAG_TIME_BOMB);


