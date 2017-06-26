#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MSQ
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MSQ.h
*********************************************************************/

#ifndef WST_MSQ_H
#define WST_MSQ_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]

//## package RXF::RXF_BehaviorPkg

//## class WST_MSQ
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_MSQ handles the asynchronous message queue of the RXF.
// 
// $Id: WST_MSQ.h 35025 2016-08-09 11:42:33Z eroemer $
// $URL: https://svn.willert.de/V6/trunk/Component/RXF/RXF/Source/CPP/WST_MSQ.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_MSQ {
    ////    Constructors and destructors    ////
    
public :

    //## operation WST_MSQ(uint16)
    WST_MSQ( uint16 size = WST_TSK_DEFAULT_MESSAGE_QUEUE_SIZE, WSTBoolean osStarted = WSTTRUE );

	//## operation WST_MSQ(uint16,void*)
	WST_MSQ( uint16 size, void* msq, WSTBoolean osStarted );
    
    //## auto_generated
    ~WST_MSQ( void );
    
    ////    Operations    ////
    
    //## operation cancelEvents(WST_FSM,WST_EVT_ID_t)
    void cancelEvents(WST_FSM* destination, const WST_EVT_ID_t id);
    
    //## operation get()
    WST_EVT* get( void );
    
    //## operation isEmpty()
    WSTBoolean isEmpty( void );
    
    //## operation put(WST_EVT)
    void put(WST_EVT* event, WSTBoolean fromISR);
	//## operation operator delete(void *)
    WST_INLINE_OP void operator delete(void * ptr)
	{
		WST_MEM::returnMemory( ptr );
	}
    
    //## operation operator new(size_t)
    WST_INLINE_OP void * operator new(size_t size)
	{
		return WST_MEM::getMemory( size );
	}
    
    ////    Additional operations    ////
    
    //## auto_generated
    WST_INLINE_OP uint16 getInitSize( void ) { return initSize; }
    
    //## auto_generated
    WST_INLINE_OP void setInitSize(uint16 p_initSize) { initSize = p_initSize; }
    
    //## auto_generated
    WST_INLINE_OP WST_RTOS_MSQ_t *getRtosMessageQueue( void ) { return &rtosMessageQueue; }
    
    //## auto_generated
    WST_INLINE_OP void setRtosMessageQueue(WST_RTOS_MSQ_t p_rtosMessageQueue) { rtosMessageQueue = p_rtosMessageQueue; }
    
    //## auto_generated
    WST_INLINE_OP void * getRtosMsgBuffer( void ) { return rtosMsgBuffer; }
    
    //## auto_generated
    WST_INLINE_OP void setRtosMsgBuffer(void * p_rtosMsgBuffer) { rtosMsgBuffer = p_rtosMsgBuffer; }
    
    ////    Attributes    ////

private :
    
    
    uint16 initSize;		//## attribute initSize
    
    WST_RTOS_MSQ_t rtosMessageQueue;		//## attribute rtosMessageQueue
    
    void * rtosMsgBuffer;		//## attribute rtosMsgBuffer
};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MSQ.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
