#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_TMR
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMR.h
*********************************************************************/

#ifndef WST_TMR_H
#define WST_TMR_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_BehaviorPkg

//## class WST_TMR
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_TMR represents a timeout in the RXF. It inherits from the WST_EVT and is handled in a similar way.
// 
// $Id: WST_TMR.h 32998 2015-09-30 10:07:36Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_TMR.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_TMR : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    virtual ~WST_TMR( void ) {} 

	//## operation operator delete(void *)
	void operator delete(void * ptr);

	//## operation operator new(size_t)
	void * operator new(size_t size);
    
    ////    Attributes    ////
    
    // Pointer to the next timeout for fast handling. We do not use STL or other lists here to manage them, but have a runtime optimized handling of a linked list for relative timeouts in the WST_TMM class.
    WST_TMR* nextTm;		//## attribute nextTm
    
    // Pointer to the previous timeout for fast handling.
    WST_TMR* prevTm;		//## attribute prevTm

    
    WST_TimeUnit_t remainingTicks;		//## attribute remainingTicks

    //## auto_generated
    void cancel();
	
#if WST_MAX_TIMEOUTS > 0
	
	//## auto_generated
	static void initTimeoutLists( void );

#endif /* WST_MAX_TIMEOUTS > 0 */
	
};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMR.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
