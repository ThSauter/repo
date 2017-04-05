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
// $Id: WST_MSQ.h 32757 2015-07-24 15:49:31Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/RXF/OORTX/Source/CPP/WST_MSQ.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// RXF-Eval_Rpy-Cpp-ARM_V6.01 (2016-02-18).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_MSQ {
    ////    Constructors and destructors    ////
    
public :

    //## operation WST_MSQ(uint16)
    WST_MSQ( );
    
    //## auto_generated
    ~WST_MSQ( void );
    
    ////    Operations    ////
    
    //## operation cancelEvents(WST_FSM,WST_EVT_ID_t)
    void cancelEvents(WST_FSM* destination, const WST_EVT_ID_t id);
    
    //## operation get()
    WST_EVT* get( void );
    
    //## operation getEventHead()
    WST_INLINE_OP WST_EVT* getEventHead( void ){ return eventHead; }
    
    //## operation isEmpty()
    WST_INLINE_OP WSTBoolean isEmpty( void ) { return ( eventHead == NULL ); }
    
    //## operation put(WST_EVT)
    void put(WST_EVT* event, WSTBoolean fromISR);
    
    //## operation startMSQ()
    void startMSQ( void );
    
    ////    Additional operations    ////
    
    
    //## auto_generated
	uint16 getEvtCount( void );
    
    ////    Attributes    ////

private :
    
    WST_EVT *eventHead;		//## attribute eventHead
	WST_EVT *eventTail;		//## attribute eventTail
    

};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MSQ.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
