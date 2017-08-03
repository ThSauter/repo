/**
*
* $Id: WSTRTOS.cpp 34182 2016-04-08 12:54:34Z eroemer $
* $URL: https://svn.willert.de/V6/trunk/Component/RTOS/KeilRTX/Source/CPP/WSTRTOS.cpp $
*
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00 (2016-04-22).
 * Copyright (c) 2011, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00/ReleaseInfo.txt
 *
 *****************************************************************************/


/* The project sources include wst.h which sets WST_H which value is tested in our include files.
 * 
 * It is not set when compiling the Rhapsody user project, in order to have WST.h include everything
 * in the right order, and 'ignore' Rhapsody generated include statements.
 */



#include "WST.h"


#include <rtl.h>


#define WST_RXF_RUNNING_START_SEC_DATA_INIT_32_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */



static volatile WST_TimeUnit_t		rxfTicks = 0;


#define WST_RXF_RUNNING_STOP_SEC_DATA_INIT_32_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */




#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

void wstMainTask( void );
extern sint16 WST_RXF_Main(sint16 argc, char_t* argv[]); 

uint32 mainTaskStack[ (WST_RTOS_MAIN_STACK_SIZE + 3) / 4 ];
uint32 mainMSQBuffer[ WST_TSK_DEFAULT_MESSAGE_QUEUE_SIZE + 4 ];

    
WST_TSK theMainTask((uint8*)mainTaskStack, (uint8*)mainMSQBuffer, WST_MAIN_TASK_PRIORITY, WST_RTOS_MAIN_STACK_SIZE , WST_TSK_DEFAULT_MESSAGE_QUEUE_SIZE, FALSE);


void wstMainTask( void )
{

	/* Start the generated main function */

	WST_OSW_TMM_initTimerTask();
	
	WST_TSK::setOS_Started( WSTTRUE ) ;
	WST_TSK *nextTask = WST_TSK::initList;
	
	#ifdef WST_MEM_USE_MUTEX
		WST_MEM_Pool::initMutex();	
	#endif
	
	while(nextTask != NULL){
		nextTask->startTaskAfterOSStart();
		nextTask = nextTask->getNext();
	}
	
	WST_TMM::getInst()->initMutex();
	
	(void) WST_RXF_Main( 0, NULL );
}


void WSTRTOS_Init( void )
{

	os_sys_init_user( wstMainTask, WST_MAIN_TASK_PRIORITY,
					  mainTaskStack, WST_RTOS_MAIN_STACK_SIZE );

	return;
}

void WSTRTOS_Cleanup( void )
{
	return;
}

#define WST_RXF_RUNNING_END_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */




#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

void WSTRTOS_incrementRxfTicks( void )
{
	rxfTicks++;
}

#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */




#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

WST_TimeUnit_t WSTRTOS_getRxfTicks( void )
{
	return rxfTicks;
}

#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */




#define WST_RXF_RUNNING_START_SEC_CODE_SLOW
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

void WSTTarget_sleep( WST_TimeUnit_t aTime ) 
{
	aTime = aTime;	/* avoid unreferenced parameter warning */
}

#define WST_RXF_RUNNING_STOP_SEC_CODE_SLOW
/* @MISRA_19.1,19.15=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */
