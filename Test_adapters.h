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

____CreateMasterModeAdapterDeclaration(Test,MY_TEST_MASTER_MODE_STEP_A);
____CreateMasterModeAdapterDeclaration(Test,MY_TEST_MASTER_MODE_STEP_B);
____CreateMasterModeAdapterDeclaration(Test,MY_TEST_MASTER_MODE_STEP_C);

____CreateSlaveModeAdapterDeclaration(Test,MY_TEST_SLAVE_MODE_STEP_A);
____CreateSlaveModeAdapterDeclaration(Test,MY_TEST_SLAVE_MODE_STEP_B);
____CreateSlaveModeAdapterDeclaration(Test,MY_TEST_SLAVE_MODE_STEP_C);

____CreateMessageTagAdapterDeclaration(Test,MY_TEST_MPI_TAG_STOP_AND_DIE);
____CreateMessageTagAdapterDeclaration(Test,MY_TEST_MPI_TAG_TIME_BOMB);

#endif
