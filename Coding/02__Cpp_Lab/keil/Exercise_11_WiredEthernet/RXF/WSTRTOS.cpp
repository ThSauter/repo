/**
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
* $Id: WSTRTOS.c 33605 2016-01-28 09:35:30Z eroemer $
* $URL: https://svn.willert.de/V6/trunk/Component/RTOS/CMSIS/Source/C/WSTRTOS.c $
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
 * Copyright (c) 2013, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01/ReleaseInfo.txt
 *
 *****************************************************************************/


#include "WST.H"

#include <cmsis_os.h>

#ifdef WST_TARGET_DEBUGGING_ENABLED
#include "WSTMonitor.h"
#endif /* WST_TARGET_DEBUGGING_ENABLED */


#define WST_RXF_RUNNING_START_SEC_DATA_INIT_32_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


static volatile WST_TimeUnit_t		rxfTicks = 0;

WST_TSK theMainTask("main", WST_RTOS_TASK_PRIORITY_NORMAL, WST_RTOS_MAIN_STACK_SIZE, WST_TSK_DEFAULT_MESSAGE_QUEUE_SIZE, false);


#define WST_RXF_RUNNING_STOP_SEC_DATA_INIT_32_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


extern sint16 WST_RXF_Main(sint16 argc, char_t* argv[]); 


void WSTRTOS_Init( void )
{
	if (!osKernelRunning ())  			/* if kernel is not running, initialize the kernel */
	{

		if (osKernelInitialize () != osOK)         /* check osStatus for other possible valid values */
		{
			WST_ERR::error( WST_ERR::WST_ERR_TASK_START_FAILED, 0U );
		}
	}
	
	
	theMainTask.getRtosTask()->id = osThreadGetId();

	if (!osKernelRunning ())                      // is the kernel running ?
	{
		if (osKernelStart () != osOK)              // start the kernel
		{                                          // kernel could not be started
			WST_ERR::error( WST_ERR::WST_ERR_TASK_START_FAILED, 0U );
		}
   }

	WST_OSW_TMM_initTimerTask();
	
	WST_TSK::setOS_Started( WSTTRUE ) ;
	WST_TSK *nextTask = WST_TSK::initList;
	
	while(nextTask != NULL){
		nextTask->startTaskAfterOSStart();
		nextTask = nextTask->getNext();
	}
	
	WST_TMM::getInst()->initMutex();
	
	/* Start the generated main function */
	(void) WST_RXF_Main( 0, NULL );

	/* Will never be reached. */
	return;
}

void WSTRTOS_Cleanup( void )
{
	return;
}


#define WST_RXF_RUNNING_END_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */




#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

void WSTRTOS_incrementRxfTicks( void )
{
	rxfTicks++;
}

#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */




#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

WST_TimeUnit_t WSTRTOS_getRxfTicks( void )
{
	return rxfTicks;
}

#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */







