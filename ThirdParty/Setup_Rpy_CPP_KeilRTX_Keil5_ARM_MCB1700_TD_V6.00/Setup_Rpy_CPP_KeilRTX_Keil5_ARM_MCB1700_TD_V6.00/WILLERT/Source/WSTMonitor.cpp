/**
* \ingroup runtime
* \class Monitor
* \brief Animation Class
*
* This class serves as monitor for the RXF when used with Animation.
*
*
* $Id: WSTMonitor.cpp 33826 2016-02-23 13:12:18Z mspieker $
* $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/CPP/WSTMonitor.cpp $
*
* Willert Software Tools - Realtime eXecution Framework
*
*
* Email: support@willert.de
*
*
*
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



#include <stdlib.h>					/* size_t prototype */


#include "WST.h"


#ifdef WST_TARGET_DEBUGGING_ENABLED

/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 19.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#define WST_ANIM_RUNNING_START_SEC_DATA_NOINIT_UNSPECIFIED_FAST
#include "WSTMemoryTypes.h"
/*lint -restore */ 


/* Global Data:
 */

#ifdef WST_RXF_RXF
uint8			WSTReceiveTaskStackmem[WST_MONITOR_RECEIVE_TASK_STACK_SIZE];

#ifndef WST_MONITORIO_REQUIRES_POLLING
void *			WSTMonitorMSQBuffer[WST_MONITOR_RECEIVE_MSQ_SIZE + 1];
WST_MSQ			*WSTMonitor_msq;
#endif	/* WST_MONITORIO_REQUIRES_POLLING */


#endif /* of WST_RXF_RXF */

struct classInitData{
	uint8 header[ 4U ];
	void* thisPtr;
	void* firstAttribute;
	classInitData *next;
};

uint8					monitorBuffer[ WST_MONITOR_BUFFER_SIZE ] ;
void*					showedObject[ WST_MONITOR_MAX_OBJECT ];
WSTBoolean				monitorFiltersEnableFlag;
WSTBoolean				monitorStopFlag;
uint16					monitorNbCmd;
WSTBoolean				monitorSendOff;
WSTBoolean				monitorTimeoutEnableFlag;
WSTMonitorBreakPoint 	*firstBreakPoint;
WSTBoolean				monitorInit = WSTFALSE;
classInitData* 		initDataStart = NULL;
classInitData* 		initDataEnd = NULL;



#ifdef WST_RXF_RXF

WST_MTX *monitorMutex = NULL;
#endif /* WST_RXF_RXF */


/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 19.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#define WST_ANIM_RUNNING_STOP_SEC_DATA_NOINIT_UNSPECIFIED_FAST
#include "WSTMemoryTypes.h"
/*lint -restore */ 


/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 19.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#define WST_ANIM_RUNNING_START_SEC_CODE_FAST
#include "WSTMemoryTypes.h"
/*lint -restore */ 

// WSTMonitor_sendTypeSize() operation will be generated model dependant during code generation in file WSTMonitor_sendTypes.cpp
extern void WSTMonitor_sendTypeSize();
void WSTMonitor_sendDataStruct( void *dataStr, uint16 length );

#ifdef WST_LIVE_ANIMATION
void WSTMonitor_sendFSMSize()
{
	static uint8 cmdBuffVersion[ 6 ];
	cmdBuffVersion[0] = WST_MONITOR_COMMAND_SEND_FSM_LENGTH;
	cmdBuffVersion[1] =	WST_MONITOR_COMMAND_SEND_FSM;
	cmdBuffVersion[2] = (uint8)sizeof(WST_FSM);
	cmdBuffVersion[3] = (uint8)(((uint16)sizeof(WST_FSM))>>8);
	cmdBuffVersion[4] = (uint8)WST_MONITOR_MAX_PARALLEL_STATES;
	cmdBuffVersion[5] = (uint8)sizeof(WSTMonitorStateType);

	WSTMonitor_sendDataStruct( cmdBuffVersion, 6U );

}
#endif	/* WST_LIVE_ANIMATION */

void WSTMonitor_init( void )
{
	
#ifdef	WST_RXF_RXF
	monitorMutex = new WST_MTX;
	
#ifndef WST_MONITORIO_REQUIRES_POLLING
	WSTMonitor_msq = new WST_MSQ(WST_MONITOR_RECEIVE_MSQ_SIZE, WSTMonitorMSQBuffer, WSTTRUE);
#endif /* WST_MONITORIO_REQUIRES_POLLING */
	
    WST_Monitor_createReceiveTask();
	
#endif	/* WST_RXF_RXF */

	monitorInit = WSTTRUE;
	monitorBuffer[ 0 ]			= (uint8)(0xFFU);
	monitorFiltersEnableFlag	= WSTFALSE;
	monitorStopFlag				= WSTFALSE;
	monitorNbCmd				= WSTFALSE;
	monitorSendOff				= WSTTRUE;
	monitorTimeoutEnableFlag	= WSTFALSE;
	firstBreakPoint 			= NULL;

	WSTMonitor_IO_Init();
	WSTMonitor_sendVersion();
#ifdef WST_LIVE_ANIMATION
	WSTMonitor_sendTypeSize();
	WSTMonitor_sendFSMSize();
	WSTMonitor_sendHighwater();
#endif	/* WST_LIVE_ANIMATION */
while( initDataStart != NULL )
	{
		WSTMonitor_sendDataStruct( initDataStart, sizeof( classInitData ) - sizeof( void *) );
		WST_MEM::returnMemory( initDataStart );
		initDataStart = initDataStart->next;
	}
}

void WSTMonitor_sendDataStruct( void *dataStr, uint16 length )
{	

	uint8	*tmp = (uint8 *) dataStr;

	  
	if ( dataStr != NULL )
#ifdef WST_MONITORIO_BYTEBASED

	{
		uint16		 j;
		
		for( j = 0U ; j < length; j++ )
		{
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 17.4, The data from the pointer is secure  */
			WSTMonitor_IO_PutByte( tmp[j] );
/*lint -restore */ 		
		}
	}

#endif	/* WST_MONITORIO_BYTEBASED */


#ifdef WST_MONITORIO_PACKETBASED
	{
		WSTMonitor_IO_PutPacket( tmp , length);
	}
#endif
}


void WSTMonitor_sendVersion( void )
{
	static uint8 cmdBuffVersion[ 3 ]= { 0U,WST_MONITOR_COMMAND_SEND_VERSION_LENGTH, WST_MONITOR_COMMAND_SEND_VERSION };
  static uint8 version[ 3 ] = { WST_MONITOR_TEST_VERSION, WST_MONITOR_MAJOR_VERSION, WST_MONITOR_VERSION };
	
	{
		WSTMonitor_sendDataStruct( cmdBuffVersion, 3U );
		WSTMonitor_sendDataStruct( &version[0], 3U );
	}
}



void WSTMonitor_performCmd( void )
{
#ifdef	WST_MONITORIO_BYTEBASED
	
	uint16				 i = 0U;
	uint16				 length ;
	uint8					 command;

#ifdef WST_LIVE_ANIMATION
	static uint32				 pTemp   = 0U;
	void				 	*ptr;
	static uint8					 cmdBuff[ 2 ];
#endif /* WST_LIVE_ANIMATION */

	length = WSTMonitor_IO_GetByte();
	command = WSTMonitor_IO_GetByte();

	if(length != 0U){
		for( i = 0U; i < length; i++ )
		{
			monitorBuffer[i] = WSTMonitor_IO_GetByte();
		}
	}

#endif	/* WST_MONITORIO_BYTEBASED */

#ifdef WST_MONITORIO_PACKETBASED

	uint16				 i = 0U;
	uint16				 length ;
	uint8				 command;
	uint8				 *msgPtr;
	
#ifdef WST_LIVE_ANIMATION
	static uint32				 pTemp   = 0U;
	void				 	*ptr;
	static uint8					 cmdBuff[ 2 ];
#endif /* WST_LIVE_ANIMATION */

	msgPtr=(uint8*)WSTMonitor_IO_GetPacket();
	length=msgPtr[0];
	command=msgPtr[1];
	msgPtr+=2;
	for( i = 0; i < length; i++ )
	{
		monitorBuffer[i] = msgPtr[i]; //WSTMonitor_IO_GetPacket();
	}
	
#endif

#ifdef WST_KEIL_IO
	monitorNbCmd=0U;
#else
	monitorNbCmd--;
#endif


	switch( command )
	{
		
#ifdef WST_LIVE_ANIMATION
		
		case WST_MONITOR_COMMAND_SUSPEND:
			/* Suspend RXF */
			WSTMonitor_suspendRxf();
			break;

		case WST_MONITOR_COMMAND_RESUME:
			/* Resume RXF */
			WSTMonitor_resumeRxf();
			break;

		case WST_MONITOR_COMMAND_SEND_ATTRIB:	
		{
			/* WSTMonitor_SendAttribute() */
      cmdBuff[ 0 ] = monitorBuffer[ sizeof(void *) ] + (uint8)sizeof(void *);
			cmdBuff[ 1 ] = command;
			 
			WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );
			ptr	  =  monitorBuffer;
			pTemp = *((uint32*)ptr);
			WSTMonitor_sendDataStruct( (void *) &pTemp, (uint16)sizeof(void *) );
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 11.3, the int value needs to be casted to an pointer to send the contant of the variable */
			WSTMonitor_sendDataStruct( (void *)  pTemp, monitorBuffer[ sizeof(void *) ] );
/*lint -restore */ 		
			break;
		}
                        
		case WST_MONITOR_COMMAND_SEND_STATE:
    {
			/* WSTMonitor_SendState() */
			
			void **pData = (void**)monitorBuffer;
			cmdBuff[ 0 ] = ( ( sizeof( WSTMonitorStateType ) * WST_MONITOR_MAX_PARALLEL_STATES ) + (uint8)sizeof( void * ) );
			cmdBuff[ 1 ] = command;
			WSTMonitor_sendDataStruct( cmdBuff, (uint8)sizeof( cmdBuff ) );
			WSTMonitor_sendDataStruct( pData, (uint8)sizeof( void * ) );

            WST_FSM *myClass = (WST_FSM *)*pData;
            WSTMonitor_sendDataStruct( myClass->activeState, (uint8)( sizeof( WSTMonitorStateType ) * WST_MONITOR_MAX_PARALLEL_STATES ) );
      
    }
			break;
	
#ifndef WST_MONITOR_MINIMIZED
		case WST_MONITOR_COMMAND_ENABLE_FILTER:
		{
			/* Enable Filter */
			
			void** adresses = (void**) monitorBuffer;

			for ( i = 0U; i < length / sizeof(void *); i++ )
			{
/* @MISRA_11.3=OFF ID-????: The int value needs to be casted to an pointer to send the contant of the variable. */
				showedObject[i] = adresses[i];
/* @MISRA_11.3=ON */
			}

			for ( i = ( length / (uint16)sizeof(void *) ); i < WST_MONITOR_MAX_OBJECT ; i++ )
			{
				showedObject[ i ] = 0;
			}
			monitorFiltersEnableFlag = WSTTRUE;
			break;
		}


		case WST_MONITOR_COMMAND_DISABLE_FILTER:
			/* disable Filter */
			monitorFiltersEnableFlag = WSTFALSE;
			break;

		case WST_MONITOR_COMMAND_SWITCH_OFF:
			/* Switch sending function off */
			monitorSendOff = WSTTRUE;
			break;
		
		case WST_MONITOR_COMMAND_SWITCH_ON:
			/* Switch sending function on */
			monitorSendOff = WSTFALSE;
			break;

#endif /* WST_MONITOR_MINIMIZED */
                        
		case WST_MONITOR_COMMAND_RECEIVE_EVENT:
			{
				WST_EVT *event = new WST_EVT();
				uint16 parameterSize = length - 12U;
				
				ptr=monitorBuffer;
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 11.3, the int value needs to be casted to an pointer to send the contant of the variable */
				pTemp = *((uint32*)ptr);
/*lint -restore */
				
                                
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 11.3, the int value needs to be casted to an pointer to use the contant of the variable */
				event->setDestination( (WST_FSM *)pTemp );
/*lint -restore */
				
				if( parameterSize > 0 ){
					uint8 *tmpEVTPtr = (uint8*)(event + 1);
					for( i = 0; i < parameterSize; i++){ 
						tmpEVTPtr[i] = monitorBuffer[ 12 + i ];
					}
				}
				event->setSize( length - 12U );	

/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 11.3, the int value needs to be casted to an pointer to use the contant of the variable */				
				ptr=(uint32 *)(monitorBuffer + 8);
/*lint -restore */
				pTemp = *((uint32*)ptr);
				if(pTemp==0U)	
				{					
					event->setSource( 0U );
				}
				else
				{
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 11.3, the int value needs to be casted to an pointer to use the contant of the variable */				
					event->setSource( (void*)(pTemp | 0x01U) ); 
/*lint -restore */
					
				}					
                              
				ptr=(&monitorBuffer[4]);
				pTemp = *((uint32*)ptr);
				event->setId( (sint16)pTemp );
       
				theMainTask.getMessageQueue()->put(event, false);
			}	
			break;
			
		case WST_MONITOR_COMMAND_ENABLE_TIMEOUT_EVENTS:
		{
			/* Enable Time out Events */
			monitorTimeoutEnableFlag = WSTTRUE;
			break;
		}

		case WST_MONITOR_COMMAND_DISABLE_TIMEOUT_EVENTS:
		{
			/* disable Time out Events */
			monitorTimeoutEnableFlag = WSTFALSE;
			break;
		}
		
		case WST_MONITOR_COMMAND_ADD_BREAKPOINT:
		{
			WSTMonitorBreakPoint *newBreakPoint = (WSTMonitorBreakPoint*)WST_MEM::getMemory( sizeof(WSTMonitorBreakPoint) );
			newBreakPoint->destination = *(WST_FSM**)monitorBuffer;
			newBreakPoint->state = *( (uint16*)&monitorBuffer[ sizeof(void*) ] );
			newBreakPoint->eventID = *( (uint16*)&monitorBuffer[ sizeof(void*) + 2 ] );
			
			newBreakPoint->next = firstBreakPoint;
			firstBreakPoint = newBreakPoint;			
			break;
		}
		
		case WST_MONITOR_COMMAND_REMOVE_BREAKPOINT:
		{
			WSTMonitorBreakPoint *tmpBreakPoint = firstBreakPoint;
			WSTMonitorBreakPoint *parent = NULL;
			WST_FSM *destination = *(WST_FSM**)monitorBuffer;
			uint16 state = *( (uint16*)&monitorBuffer[ sizeof(void*) ] );
			uint16 eventID = *( (uint16*)&monitorBuffer[ sizeof(void*) + 2 ] );
			
			while( tmpBreakPoint != NULL ){
				if( (uint32)tmpBreakPoint->destination == (uint32)destination && (uint16)tmpBreakPoint->eventID == (uint16)eventID && (uint16)tmpBreakPoint->state == (uint16)state ){
					if( parent == NULL ){
						firstBreakPoint = tmpBreakPoint->next;
					}
					else
					{
						parent->next = tmpBreakPoint->next;
					}
					WST_MEM::returnMemory( tmpBreakPoint );
					tmpBreakPoint = NULL;
				}
				else{
					parent = tmpBreakPoint;
					tmpBreakPoint = tmpBreakPoint->next;
				}
			}			
			break;
		}

#endif /* WST_LIVE_ANIMATION */
		case WST_MONITOR_COMMAND_RTC_START_CASE:
		{
#ifdef WST_TESTCONDUCTOR
			/* Signals the Testharnes to start a specific case (implementation comming soon)*/
			for( i = 0; i < length; i++)
			{
				GlobalTestCaseVar[i] = monitorBuffer[i];
			}
#endif /* WST_TESTCONDUCTOR */
			break;
		}

		default: 
			break;
	}	
}


#ifdef WST_MONITORIO_REQUIRES_POLLING

void WSTMonitor_pollIncomingData( void )
{
	WSTMonitorIO_receiveIncomingData( );
}

#endif	/* WST_MONITORIO_REQUIRES_POLLING */

#ifdef WST_LIVE_ANIMATION

void WSTMonitor_suspendRxf( void )
{
	monitorStopFlag = WSTTRUE; 
}


void WSTMonitor_resumeRxf( void )
{
	monitorStopFlag = WSTFALSE;
}


void WSTMonitor_sendInit( void *me, uint16 id, void *firstAttributeAddress )
{
	static uint8 cmdBuff[ 4 ] = { 2U + sizeof(void *) + sizeof(void *), WST_MONITOR_COMMAND_SEND_INIT, 0U, 0U };

	if( monitorInit == WSTFALSE )
	{
		classInitData * newData = (classInitData *)WST_MEM::getMemory( sizeof( classInitData ) );
		newData->header[ 0 ] = 2U + sizeof(void *) + sizeof(void *);
		newData->header[ 1 ] = WST_MONITOR_COMMAND_SEND_INIT;
		newData->header[ 2 ] = (uint8)id;
		newData->header[ 3 ] = (uint8)(id>>8U);
		newData->thisPtr = me;
		newData->firstAttribute = firstAttributeAddress;
		if( initDataStart == NULL )
		{
			initDataStart = newData;
			initDataEnd = newData;
		}
		else
		{
			initDataEnd->next = newData;
			initDataEnd = newData;
			newData->next = NULL;
		}
		return;
	}
	cmdBuff[2] = (uint8)id;
	cmdBuff[3] = (uint8)(id>>8U);

	if ( me != NULL )
	{

#ifdef	WST_RXF_RXF
		if( monitorMutex != NULL ){
			WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */
		}

#endif	/* WST_RXF_RXF */

		WSTMonitor_sendDataStruct( cmdBuff, 4U );
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 1.2, There will be no accass to the data of the pointer */				
		WSTMonitor_sendDataStruct( &me, sizeof(void*) );
		WSTMonitor_sendDataStruct( &firstAttributeAddress, sizeof(void*) );
/*lint -restore */
		

#ifdef	WST_RXF_RXF
		if( monitorMutex != NULL ){
			WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */
		}

#endif	/* WST_RXF_RXF */
	}
}


void WSTMonitor_sendDestroy( void *me )
{

#ifndef WST_MONITOR_MINIMIZED
  
	static uint8 cmdBuff[ 2 ]= { sizeof(void*), WST_MONITOR_COMMAND_SEND_DESTROY };

	if ( me == NULL )
	{
#ifdef	WST_RXF_RXF

		WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

		WSTMonitor_sendDataStruct( cmdBuff, 2U );
		WSTMonitor_sendDataStruct( me, sizeof(void*) );
		
#ifdef	WST_RXF_RXF

		WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
	}
#endif /* WST_MONITOR_MINIMIZED */

        
}

void WSTMonitor_sendOpCall( void* destination, void* source, uint16 id, void* parmStart, void* paramEnd)
{
	uint8 cmdBuff[ 2 ];
	uint8 parameterSize = (uint32)paramEnd - (uint32)parmStart;
	uint32 currentTicks;
	cmdBuff[ 0 ] = sizeof(void*) * 2 + 2  + parameterSize;
	cmdBuff[ 1 ] = WST_MONITOR_COMMAND_SEND_OPERATION;
	
	currentTicks = WSTRTOS_getRxfTicks();

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

	WSTMonitor_sendDataStruct( cmdBuff, 2U );
	WSTMonitor_sendDataStruct( &source, sizeof(void*) );
	WSTMonitor_sendDataStruct( &destination, sizeof(void*) );
	WSTMonitor_sendDataStruct( &currentTicks, 4 );	
	WSTMonitor_sendDataStruct( &id, 2 );
	WSTMonitor_sendDataStruct( parmStart, parameterSize );


#ifdef	WST_RXF_RXF

	WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
	
}

void WSTMonitor_sendEvent( uint8 pEventData[], uint8 parameterSize, uint8 *parameter )
{
	if ( pEventData != NULL )
	{
		WSTBoolean isInstanceFiltered;

		isInstanceFiltered = WSTMonitor_isFiltered( ((void**)pEventData)[1] );

		if ( ( monitorFiltersEnableFlag == WSTFALSE ) || ( isInstanceFiltered == WSTTRUE ) )
		{
			static uint8 cmdBuff[ 2 ];
			cmdBuff[ 0 ] = sizeof(void*) * 2 + 6 + ( sizeof( WSTMonitorStateType) * WST_MONITOR_MAX_PARALLEL_STATES ) + parameterSize;
			cmdBuff[ 1 ] = WST_MONITOR_COMMAND_SEND_EVENT;

#ifdef	WST_RXF_RXF

			WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

			WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );
			WSTMonitor_sendDataStruct( pEventData, sizeof(void*) * 2 + 6 + ( sizeof( WSTMonitorStateType) * WST_MONITOR_MAX_PARALLEL_STATES ) );
			
			if( parameterSize > 0 ){
				WSTMonitor_sendDataStruct( (uint8*)(parameter), parameterSize);
			}

#ifdef	WST_RXF_RXF

			WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
		}
	}
}


void WSTMonitor_sendTimeOut( uint8 pEventData[] )
{
	if ( pEventData != NULL )
	{
		WSTBoolean isInstanceFiltered;
		isInstanceFiltered = WSTMonitor_isFiltered( ((void**)pEventData)[0] );
    
		if ( ( monitorFiltersEnableFlag == WSTFALSE ) || ( isInstanceFiltered == WSTTRUE ) )
		{
			static uint8 cmdBuff[ 2 ]= { sizeof(void*) + 4 + ( sizeof( WSTMonitorStateType) * WST_MONITOR_MAX_PARALLEL_STATES ), WST_MONITOR_COMMAND_SEND_TIMEOUT };

#ifdef	WST_RXF_RXF

			WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

			WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );
			WSTMonitor_sendDataStruct( pEventData, sizeof(void*) + 4 + ( sizeof( WSTMonitorStateType) * WST_MONITOR_MAX_PARALLEL_STATES ) );

#ifdef	WST_RXF_RXF

			WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
		}
	}
}


void WSTMonitor_sendError( void )
{
	static uint8 cmdBuff[ 2 ]= { WST_MONITOR_COMMAND_SEND_ERROR_LENGTH, WST_MONITOR_COMMAND_SEND_ERROR };

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

	WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
}


WSTBoolean WSTMonitor_isFiltered( const void *ptr )
{
	uint8 i;
	WSTBoolean returnValue = WSTFALSE;
	
	for( i = 0U; i < WST_MONITOR_MAX_OBJECT; i++ )
	{
		if( ptr == showedObject[ i ] )
		{
			returnValue = WSTTRUE;
			break;
		}
	}
	return returnValue;
}


void WSTMonitor_sendBufferReset( void )
{
	static uint8 cmdBuff[ 2 ] = { WST_MONITOR_COMMAND_SEND_BUFFER_RESET_LENGTH, WST_MONITOR_COMMAND_SEND_BUFFER_RESET };
	
#ifdef	WST_RXF_RXF

	WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

	WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
	
}


void WSTMonitor_sendHighwater()
{
#ifdef WST_CFG_HIGHWATERMARKS
	static uint8 cmdBuffVersion[ 2 ]= { sizeof(void*),WST_MONITOR_COMMAND_SEND_HIGHWATER };
	void* highwaterPtr;
	#if WST_INITIAL_TINY_BUFFERS > 0
	highwaterPtr= &WST_CFG_Highwater::tinyBuffersMax;
	#elif WST_INITIAL_SMALL_BUFFERS > 0
	highwaterPtr= &WST_CFG_Highwater::smallBuffersMax;	
	#elif WST_INITIAL_MEDIUM_BUFFERS > 0
	highwaterPtr= &WST_CFG_Highwater::mediumBuffersMax;		
	#elif WST_INITIAL_LARGE_BUFFERS > 0
	highwaterPtr= &WST_CFG_Highwater::largeBuffersMax;
	#elif WST_INITIAL_HUGE_BUFFERS > 0
	highwaterPtr= &WST_CFG_Highwater::hugeBuffersMax;
	#else
	highwaterPtr= &WST_CFG_Highwater::timeoutsMax;
	#endif /* WST_INITIAL_HUGE_BUFFERS */
	

	WSTMonitor_sendDataStruct( cmdBuffVersion, (uint16)sizeof( cmdBuffVersion ) );

	WSTMonitor_sendDataStruct( (void *) &highwaterPtr, sizeof(void *) );
#endif /* WST_CFG_HIGHWATERMARKS */
}

#endif /* WST_LIVE_ANIMATION */


#ifdef WST_RXF_RXF

void WST_Monitor_receiveTask(void *x)
{

	while(1)
	{
#ifdef WST_MONITORIO_REQUIRES_POLLING
		WSTMonitorIO_receiveIncomingData();
#else
		WSTMonitor_msq->get();
#endif /* WST_MONITORIO_REQUIRES_POLLING */
		if (monitorNbCmd > 0)
		{
			/* If there is received data in the buffer, try to perform the received command. */
			WSTMonitor_performCmd();
		}
   }
}


void WST_Monitor_createReceiveTask()
{
/* Task creation for Monitor Task: */
	WST_OSW_TSK_userInit ( WST_Monitor_receiveTask,  WST_MONITOR_TASK_PRIORITY, WSTReceiveTaskStackmem, WST_MONITOR_RECEIVE_TASK_STACK_SIZE, NULL ); 
}


#endif /* of WST_RXF_RXF */


#ifdef WST_RXF_MINIRXF

void WST_Monitor_sendTextStart( void )
{
	WSTMonitor_IO_PutByte( 0 );	
	WSTMonitor_IO_PutByte( WST_MONITOR_COMMAND_SEND_TEXT );
}

void WST_Monitor_sendTextChar( char_t character )
{
	WSTMonitor_IO_PutByte( (int) character );
}

void WST_Monitor_sendTextStop( void )
{
	WSTMonitor_IO_PutByte( 0 );	
}


#endif /* of WST_RXF_MINIRXF */



#ifdef WST_TESTCONDUCTOR

void WSTMonitor_sendRTCInfo( uint32 e, uint32 ln, uint32 nr )
{
	static uint8 cmdBuff[ 2 ] = { WST_MONITOR_COMMAND_SEND_RTC_INFO_LENGTH , WST_MONITOR_COMMAND_SEND_RTC_MSG };
	static uint32 msg[3];
	msg[0] = e;
	msg[1] = ln;
	msg[2] = nr;

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

	WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );
	WSTMonitor_sendDataStruct( msg, (uint16)sizeof( msg ) );

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
}

void WSTMonitor_sendRTCCovInfo( char* c, uint32 i, uint32 j )
{
	static uint8 cmdBuff[ 2 ] = { 0U , WST_MONITOR_COMMAND_SEND_RTC_COV_MSG };
	static uint32 msg[2];
	msg[0] = i;
	msg[1] = j;

	cmdBuff[0] = WST_MONITOR_COMMAND_SEND_RTC_COV_LENGTH + strlen(c);


#ifdef	WST_RXF_RXF

	WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

	WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );
	WSTMonitor_sendDataStruct( msg, (uint16)sizeof( msg ) );
	WSTMonitor_sendDataStruct( c, strlen(c) + 1U );


#ifdef	WST_RXF_RXF

	WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
}

void WSTMonitor_RTC_Exit( void )
{
	static uint8 cmdBuff[ 2 ] = { 0 , WST_MONITOR_COMMAND_SEND_RTC_EXIT };

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_enterCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */

	WSTMonitor_sendDataStruct( cmdBuff, (uint16)sizeof( cmdBuff ) );

#ifdef	WST_RXF_RXF

	WST_OSW_MTX_exitCriticalRegion( monitorMutex );	/* This function will complain itself on failure */

#endif	/* WST_RXF_RXF */
}

#endif /* WST_TESTCONDUCTOR */

/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 19.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#define WST_ANIM_RUNNING_STOP_SEC_CODE_FAST
#include "WSTMemoryTypes.h"
/*lint -restore */ 

#endif  /* WST_TARGET_DEBUGGING_ENABLED */
