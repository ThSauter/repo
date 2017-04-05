#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_FSM
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_FSM.h
*********************************************************************/

#ifndef WST_FSM_H
#define WST_FSM_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_BehaviorPkg

//## class WST_FSM
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_FSM supports the implementation of finite state machines using the RXF.
// 
// $Id: WST_FSM.h 32946 2015-09-08 13:35:34Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_FSM.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// RXF-Eval_Rpy-Cpp-ARM_V6.01 (2016-02-18).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.

#define MAX_NULL_STEPS 7

class WST_FSM {
public :

    //## type TakeEventStatus
    enum TakeEventStatus {
        WST_EVT_handleEventNotConsumed = 0,
        WST_EVT_handleEventError = 1,
        WST_EVT_handleEventConsumed = 2,
        WST_EVT_handleEventCompleted = 3,
        WST_EVT_handleEventInCleanup = 4,
        WST_EVT_handleEventReachTerminate = 5
    };
    
    //## type status_t
    enum status_t {
        statusDefault = 0x00U,
        statusTerminating = 0x01U,
        statusBusy = 0x02U,
        statusInCleanup = 0x04U,
        statusShouldDelete = 0x08U,
        statusStarted = 0x10U,
        statusShouldCompleteStartBehavior = 0x20U
        ,
        statusFALSE = 0x00U
    };
    
    ////    Constructors and destructors    ////
    
    //## operation WST_FSM(WST_TSK)
    WST_FSM();
    
    //## operation ~WST_FSM()
    virtual ~WST_FSM( void );
    
    ////    Operations    ////
    
    //## operation cancel(WST_TMR)
    void cancel(WST_TMR* timeout);
    
    //## operation cancelEventsAndTimeouts()
    void cancelEventsAndTimeouts( void );
    
    //## operation destroy()
    void destroy( void );
    
    //## operation endBehavior()
    void endBehavior( void );
    
    //## operation gen(WST_EVT)
    WSTBoolean gen(WST_EVT* event, WSTBoolean fromISR );
    
    //## operation handleSyncEvent(WST_EVT)
    TakeEventStatus handleSyncEvent(WST_EVT* event);
    
    //## operation popNullTransition()
    void popNullTransition( void );
    
    //## operation pushNullTransition()
    void pushNullTransition( void );
    
    //## operation rootState_entDef()
    virtual void rootState_entDef( void );
	
	//## operation cancelTimeout(const WST_TMR*)
	virtual bool cancelTimeout( const WST_TMR* );
    
    //## operation rootState_processEvent()
    virtual TakeEventStatus rootState_processEvent( void );
    
    // Arguments:
    // delay: delaytime
    // stateName: Name of current state
    //## operation scheduleTimeout(uint16,char*)
    WST_TMR* scheduleTimeout(const WST_TimeUnit_t delay, char *);
    
    //## operation setShouldDelete(bool)
    void setShouldDelete(bool b);
    
    //## operation setTask(WST_TSK,bool)
    void setTask(WST_TSK* ownerTaskPtr = 0, WSTBoolean isActive = false);
    
    //## operation startBehavior()
    WSTBoolean startBehavior( void );
    
    //## operation takeEvent(WST_EVT)
    TakeEventStatus takeEvent(WST_EVT* event);
    
    //## operation terminate()
    void terminate( void );
	
    //## operation send(WST_EVT)
	virtual bool send( WST_EVT *event);
	
    //## operation send(WST_EVT,void*)
	virtual bool send( WST_EVT *event, const void* &params );

    //## operation handleTrigger(WST_EVT)
    void handleTrigger(WST_EVT* event);
	
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


private :

    //## operation consumeGivenEvent(WST_EVT)
    void consumeGivenEvent(WST_EVT* event);
    
    //## operation inNullConfig()
    WSTBoolean inNullConfig( void );
    
    //## operation isBehaviorStarted()
	WST_INLINE_OP WSTBoolean isBehaviorStarted(void) { return (status & statusStarted) == statusStarted; }
    
    //## operation isBusy()
	WST_INLINE_OP WSTBoolean isBusy(void) { return (status & statusBusy) == statusBusy; }
    
    //## operation isInCleanup()
	WST_INLINE_OP WSTBoolean isInCleanup(void) { return (status & statusInCleanup) == statusInCleanup; }
    
    //## operation runToCompletion()
    WSTBoolean runToCompletion( void );
    
    //## operation setBehaviorStarted(bool)
    void setBehaviorStarted(WSTBoolean b);
    
    //## operation setCompleteStartBehavior(bool)
    void setCompleteStartBehavior(WSTBoolean b);
    
    //## operation setShouldTerminate(bool)
    void setShouldTerminate(WSTBoolean b);
    
    //## operation shouldCompleteRun()
    WSTBoolean shouldCompleteRun( void );
    
    //## operation shouldCompleteStartBehavior()
	WST_INLINE_OP WSTBoolean shouldCompleteStartBehavior(void) { return (status & statusShouldCompleteStartBehavior) == statusShouldCompleteStartBehavior; }
    
    //## operation shouldDelete()
	WST_INLINE_OP WSTBoolean shouldDelete(void) { return (status & statusShouldDelete) == statusShouldDelete; }
    
    //## operation shouldTerminate()
	WST_INLINE_OP WSTBoolean shouldTerminate(void) { return (status & statusTerminating) == statusTerminating; }
    
    ////    Additional operations    ////

public :

    //## auto_generated
    WST_INLINE_OP uint16 getRootState_active( void ) { return rootState_active; }
    
    //## auto_generated
    WST_INLINE_OP WST_EVT* getCurrentEvent( void ) { return currentEvent; }
    
    //## auto_generated
    void setCurrentEvent(WST_EVT* p_WST_EVT);
    
    //## auto_generated
    WST_INLINE_OP WST_TSK* getOwnerTask( void ) { return ownerTask; }
    
#ifdef WST_LIVE_ANIMATION
    //## auto_generated
    WST_INLINE_OP void setOwner( void* p_owner ) { owner = p_owner; }
#endif /* WST_LIVE_ANIMATION */
    
    //## auto_generated
    WST_INLINE_OP void setTask(WST_TSK* p_WST_TSK) {ownerTask = p_WST_TSK; }

	
    //## auto_generated
    void cleanUpRelations( void );
    
    ////    Attributes    ////
	
#ifdef WST_LIVE_ANIMATION
	WSTMonitorStateType activeState[WST_MONITOR_MAX_PARALLEL_STATES];
#endif /* WST_LIVE_ANIMATION */

protected :
	
	uint16 rootState_active;		//## attribute rootState_active

private :
    
    uint8 nullTransitionCount;		//## attribute nullTransitionCount
    
    uint8 status;		//## attribute status
    
    ////    Relations and components    ////
    
    WST_EVT* currentEvent;		//## link currentEvent
    
    WST_TSK* ownerTask;		//## link ownerTask
    

#ifdef WST_LIVE_ANIMATION 	    
	void* owner;		//## attribute owner
#endif /* WST_LIVE_ANIMATION */

};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_FSM.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
