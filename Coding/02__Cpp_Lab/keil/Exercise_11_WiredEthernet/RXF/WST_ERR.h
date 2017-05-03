#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_ERR
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_ERR.h
*********************************************************************/

#ifndef WST_ERR_H
#define WST_ERR_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_CorePkg

//## class WST_ERR
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_ERR is the RXF error handler and defines the list of available error codes.
// The error() method need to be implemented application specific by the end-user.
// 
// $Id: WST_ERR.h 32757 2015-07-24 15:49:31Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_ERR.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_ERR {
public :

    //## type ErrorCode
    enum ErrorCode {
        WST_ERR_NONE = 0,
        WST_ERR_EMPTY_ME_PTR = 1,
        WST_ERR_EVENT_QUEUE_FULL = 2,
        WST_ERR_EVENT_NULL = 3,
        WST_ERR_EVENT_QUEUE_EMPTY = 4,
        WST_ERR_EVENT_CANCELLED = 5,
        WST_ERR_EVENT_DISCARDED = 6,
        WST_ERR_EVENT_NULL_DEST = 7,
        WST_ERR_TIMEOUT_HEAP_FULL = 8,
        WST_ERR_TIMEOUT_NOT_FOUND = 9,
        WST_ERR_REALLOC_MEMORYPOOL = 10,
        WST_ERR_INFINITE_NULL_TRANSITIONS = 11,
        WST_ERR_NO_LAST_STATE_IN_HISTORY = 12,
        WST_ERR_TOO_MANY_NULL_CONFIGS = 13,
        WST_ERR_TOO_FEW_NULL_CONFIGS = 14,
        WST_ERR_NULL_DESTINATION = 15,
        WST_ERR_ALLOCATING_ANOTHER_MEMORYPOOL = 16,
        WST_ERR_EMPTY_MEMORY_PTR = 17,
        WST_ERR_EMPTY_VTBL_PTR = 18,
        WST_ERR_EMPTY_STATE_PTR = 19,
        WST_ERR_EMPTY_STR_PTR = 20,
        WST_ERR_CONFIG_ERROR = 21,
        WST_ERR_CONFIG_ERROR_LARGER = 22,
        WST_ERR_NO_MALLOC = 23,
        WST_ERR_ALLOC_FAILED = 24,
        WST_ERR_NOT_IMPLEMENTED = 25,
        WST_ERR_VERSION_ERROR = 26,
        WST_ERR_INVALID_MEMORY_PTR = 27,
        WST_ERR_ALLOC_TOO_LARGE = 28,
		WST_ERR_TIMER_TASK_START_FAILED = 29,
		WST_ERR_MSQ_INIT_FAILED = 30,
		WST_ERR_MSQ_SEND_FAILED = 31,
		WST_ERR_MSQ_GET_FAILED = 32,
		WST_ERR_MTX_UNLOCK_FAILED = 33,
		WST_ERR_MTX_LOCK_FAILED = 34,
		WST_ERR_MTX_INIT_FAILED = 35,
		WST_ERR_MTX_CLEANUP_FAILED = 36,
		WST_ERR_CND_WAIT_FAILED = 37,
		WST_ERR_CND_SIGNAL_FAILED = 38,
		WST_ERR_TASK_STOP_FAILED = 39,
        WST_ERR_TASK_START_FAILED = 40,
		WST_ERR_MEM_GET_CORRUPT = 41,
		WST_ERR_MEM_RETURN_CORRUPT = 42,

        WST_ERR_ANIMATION_INIT_FAILED = 70, // We use 70 and up for the animation error codes
        WST_ERR_ANIMATION_IO_FAILED = 71,

        WST_ERR_CON_LST_INVALID = 80, // We use 80 and up for container class related errors
        WST_ERR_CON_LST_EMPTY = 81,

		WST_ERR_TEST_SUCCESS = 123 // Error code reserved for automated RXF testing
    };
    
    //## type AdditionalErorArgument
    typedef uint32 AdditionalErorArgument;
    
    ////    Constructors and destructors    ////
    
    //## auto_generated
    ~WST_ERR( void );
    
    ////    Operations    ////
    
    //## operation error(ErrorCode,AdditionalErorArgument)
    static void error(const ErrorCode& wstErrorCode, const AdditionalErorArgument& additionalArg);
};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_ERR.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
