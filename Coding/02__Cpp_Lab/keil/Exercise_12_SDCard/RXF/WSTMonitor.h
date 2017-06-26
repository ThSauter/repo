#ifndef WSTMONITOR_H
#define WSTMONITOR_H

/**
* $Id: WSTMonitor.h 35905 2016-11-15 12:56:46Z mspieker $
* $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/Common/WSTMonitor.h $
*
* Willert Software Tools - Monitor I/O
*
* Email: support@willert.de
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
 * Copyright (c) 2011, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01/ReleaseInfo.txt
 *
 *****************************************************************************/




/* Constants:
 *
 */
 
 #ifdef WST_RXF_RXF

#define WST_MONITOR_RECEIVE_TASK_STACK_SIZE			512U
#define WST_MONITOR_RECEIVE_MSQ_SIZE				10U

#endif /* of WST_RXF_RXF */

#define WST_MONITOR_BUFFER_SIZE						32U
#define WST_MONITOR_MAX_OBJECT 		 				 8U
#define WST_MONITOR_MAX_PARALLEL_STATES				 4U
typedef uint8 WSTMonitorStateType;


#define WST_MONITOR_COMMAND_SUSPEND					 0U
#define WST_MONITOR_COMMAND_RESUME					 1U
#define WST_MONITOR_COMMAND_SEND_DATA				 2U
#define WST_MONITOR_COMMAND_STOP_DATA				 3U
#define WST_MONITOR_COMMAND_SEND_ATTRIB				 4U
#define WST_MONITOR_COMMAND_SEND_STATE				 5U
#define WST_MONITOR_COMMAND_SEND_ERROR				 6U
#define WST_MONITOR_COMMAND_SEND_INIT				 7U
#define WST_MONITOR_COMMAND_SEND_DESTROY			 8U
#define WST_MONITOR_COMMAND_SEND_EVENT_CREATE		 9U
#define WST_MONITOR_COMMAND_SEND_EVENT_START		10U
#define WST_MONITOR_COMMAND_SEND_EVENT_END			11U
#define WST_MONITOR_COMMAND_SEND_RTC_MSG			12U
#define WST_MONITOR_COMMAND_SWITCH_OFF				13U
#define WST_MONITOR_COMMAND_SWITCH_ON				14U
#define WST_MONITOR_COMMAND_RECEIVE_EVENT			15U
#define WST_MONITOR_COMMAND_SEND_VERSION			16U
#define WST_MONITOR_COMMAND_BUFFER_OVERFLOW			17U
#define WST_MONITOR_COMMAND_ENABLE_TIMEOUT_EVENTS	18U 
#define WST_MONITOR_COMMAND_DISABLE_TIMEOUT_EVENTS	19U
#define WST_MONITOR_COMMAND_SEND_TIMEOUT			20U
#define WST_MONITOR_COMMAND_SEND_BUFFER_RESET		21U
#define WST_MONITOR_COMMAND_SEND_TEXT				22U
#define WST_MONITOR_COMMAND_SEND_HIGHWATER			23U
#define WST_MONITOR_COMMAND_SEND_STATESIZE			24U
#define WST_MONITOR_COMMAND_RTC_START_CASE			26U
#define WST_MONITOR_COMMAND_SEND_RTC_EXIT			27U
#define WST_MONITOR_COMMAND_SEND_RTC_COV_MSG		28U
#define WST_MONITOR_COMMAND_ADD_BREAKPOINT			30U
#define WST_MONITOR_COMMAND_REMOVE_BREAKPOINT		31U
#define WST_MONITOR_COMMAND_RTC_STOP				32U
#define WST_MONITOR_COMMAND_SEND_OPERATION			33U
#define WST_MONITOR_COMMAND_SEND_TYPES				34U


#define WST_MONITOR_COMMAND_SEND_VERSION_LENGTH		 3U 
#define WST_MONITOR_COMMAND_SEND_EVENT_START_LENGTH	 6U
#define WST_MONITOR_COMMAND_SEND_EVENT_CREATE_TIMEOUT	 10U
#define WST_MONITOR_COMMAND_SEND_EVENT_END_LENGTH	 2 + sizeof( WSTMonitorStateType ) * WST_MONITOR_MAX_PARALLEL_STATES
#define WST_MONITOR_COMMAND_SEND_ERROR_LENGTH		 0U
#define WST_MONITOR_COMMAND_SEND_RTC_INFO_LENGTH	12U
#define WST_MONITOR_COMMAND_SEND_RTC_COV_LENGTH	 	 9U
#define WST_MONITOR_COMMAND_SEND_BUFFER_RESET_LENGTH 0U
#define WST_MONITOR_COMMAND_SEND_STATESIZE_LENGTH	 2U

#define WST_MONITOR_TEST_VERSION					 4U
#define WST_MONITOR_MAJOR_VERSION					 0U
#define WST_MONITOR_VERSION							 0U



/* Declaration global data in WSTMonitor.c for external access:
 *
 */

#define WST_ANIM_RUNNING_START_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


typedef struct WSTMonitorBreakPoint_t WSTMonitorBreakPoint;

extern WSTBoolean				monitorTimeoutEnableFlag;
extern WSTBoolean				monitorStopFlag;
extern uint16					WSTmonitorBytesAvailable;
extern WSTBoolean				monitorSendOff;
extern WST_MSQ					*WSTMonitor_msq;
extern WSTMonitorBreakPoint 	*firstBreakPoint;
extern uint32 					WSTMonitorEventID;
extern WSTBoolean				monitorNbCmd;



typedef struct WSTMonitorEventCreate_t WSTMonitorEventCreate;
struct WSTMonitorEventCreate_t{
  void *source;
	void *destination;
	uint32 currentTick;
	uint16 eventID;
	sint16 id;
};

typedef struct WSTMonitorEventStart_t WSTMonitorEventStart;
struct WSTMonitorEventStart_t{
	uint32 currentTick;
	uint16 eventID; 
};

typedef struct WSTMonitorEventEnd_t WSTMonitorEventEnd;
struct WSTMonitorEventEnd_t{
	uint16 eventID;
	WSTMonitorStateType currentState[WST_MONITOR_MAX_PARALLEL_STATES];
};

typedef struct WSTMonitorTimeoutEvent_t WSTMonitorTimeoutEvent;
struct WSTMonitorTimeoutEvent_t{
	void *destination;
	uint32 currentTick;
	uint16 eventID;
};

struct WSTMonitorBreakPoint_t{
	void *destination;
	uint16 state;
	sint16 eventID;
	WSTMonitorBreakPoint* next;
};


#define WST_ANIM_RUNNING_STOP_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


/* Function prototypes and macros:
 *
 */

#define WST_ANIM_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

void					WSTMonitor_init( void );
void					WSTMonitor_sendVersion( void );
void					WSTMonitor_performCmd( void );
void					WSTMonitor_suspendRxf( void );
void					WSTMonitor_resumeRxf( void );
void					WSTMonitor_sendInit( void *me, uint16 id, void *firstAttributeAddress  );
void 					WSTMonitor_sendDestroy( void *me );
void 					WSTMonitor_sendEventCreate( uint8 pEventData[], uint8 parameterSize, uint8 *parameter );
void 					WSTMonitor_sendEventStart( uint8 pEventData[] );
void 					WSTMonitor_sendEventEnd( uint8 pEventData[] );
void 					WSTMonitor_sendTimeOut( uint8 pEventData[] );
void					WSTMonitor_sendError( void );
void 					WSTMonitor_sendRTCInfo( uint32 e, uint32 ln, uint32 nr );
void					WSTMonitor_sendRTCCovInfo( char* c, uint32 i, uint32 j );
void 					WSTMonitor_sendBufferReset( void );
void					WSTMonitor_sendHighwater( void );
void					WSTMonitor_deleteEvent( void *ptr );
void					WSTMonitor_RTC_Exit( void );
void 					WSTMonitor_sendOpCall( void* destination, void* source, uint16 id, void* parmStart, void* paramEnd);

#ifdef WST_RXF_RXF

void 			WST_Monitor_createReceiveTask( void );
void 			WST_Monitor_receiveTask( void* );
void			WSTMonitor_wakeUpTask( void );

#endif /* of WST_RXF_RXF */


#ifdef WST_RXF_MINIRXF

void 			WST_Monitor_sendTextStart( void );
void 			WST_Monitor_sendTextChar( char_t character );
void 			WST_Monitor_sendTextStop( void );

#endif /* of WST_RXF_MINIRXF */

#ifdef WST_RXF_RXF
void WSTMonitor_initMutex( void );
#endif	/* WST_RXF_RXF */

#ifdef WST_TESTCONDUCTOR
extern char GlobalTestCaseVar[32];
#endif /* WST_TESTCONDUCTOR */

#ifdef WST_MONITORIO_REQUIRES_POLLING

void WSTMonitor_pollIncomingData( void );

#else	/* WST_MONITORIO_REQUIRES_POLLING */

/* Define function as empty macro to reduce overhead. */
#define WSTMonitor_pollIncomingData() 

#endif	/* WST_MONITORIO_REQUIRES_POLLING */

#define WST_ANIM_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

#endif /* of WSTMONITOR_H */
