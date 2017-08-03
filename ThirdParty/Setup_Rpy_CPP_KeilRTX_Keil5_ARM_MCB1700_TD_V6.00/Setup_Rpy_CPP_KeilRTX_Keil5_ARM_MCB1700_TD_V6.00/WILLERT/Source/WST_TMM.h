#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_TMM
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMM.h
*********************************************************************/

#ifndef WST_TMM_H
#define WST_TMM_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_BehaviorPkg

//## class WST_TMM
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_TMM is the RXF timer manager keeping track of the timeouts in a queue.
// 
// $Id: WST_TMM.h 34229 2016-04-14 12:35:49Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_TMM.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00 (2016-04-22).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_TMM {
public :

//#[ ignore
    public:
    	static WST_TMM* getInst();
	
    	WST_TMM();
    	
    private:
    	static WST_TMM inst;
//#]

    ////    Operations    ////
    
public :

    //## operation WSTTimeToTicks(WST_TimeUnit_t)
    WST_TimeUnit_t WSTTimeToTicks(WST_TimeUnit_t delayTime);
    
    //## operation cancelEvents(WST_FSM *)
    void cancelEvents(WST_FSM * destination);
    
    //## operation getExpiredTimeout()
    WST_TMR* getExpiredTimeout( void );
    
    //## operation processTimeouts()
    void processTimeouts( void );
    
    //## operation start(WST_TimeUnit_t,WST_FSM *)
    WST_TMR* start(WST_TimeUnit_t delayTime, WST_FSM * destination);
    
    //## operation stop(WST_TMR)
    void stop(WST_TMR* timeoutToStop);
    
    //## operation tick(sint16)
    void tick(sint16 elapsedTime);
    
    ////    Additional operations    ////
    
    
    //## auto_generated
    WST_INLINE_OP WST_TMR* getItsBusyList( void ) { return itsBusyList; }
    
    //## auto_generated
    WST_INLINE_OP void setItsBusyList(WST_TMR* p_WST_TMR) { itsBusyList = p_WST_TMR; }
	

	
	//## auto_generated
	void initMutex();
    
    ////    Attributes    ////

private :

    WST_TimeUnit_t processedTicks;		//## attribute processedTicks
    
    ////    Relations and components    ////
    
    WST_TMR* itsBusyList;		//## link itsBusyList

	WST_MTX *mutex;

#ifdef WST_CFG_HIGHWATERMARKS
	uint16 usedTimeouts;
#endif /* WST_CFG_HIGHWATERMARKS */
};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMM.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
