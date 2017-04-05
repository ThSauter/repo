#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_CFG_Highwater
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_CFG_Highwater.h
*********************************************************************/

#ifndef WST_CFG_Highwater_H
#define WST_CFG_Highwater_H

 

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_BridgePkg

//## class WST_CFG_Highwater
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_CFG_Highwater is used to keep track of the maximum used memory buffers, timer queue and event queue entries. This allows optimization of the dimensions after a runtime analysis.
// 
// $Id: WST_CFG_Highwater.h 32851 2015-08-11 13:03:13Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_CFG_Highwater.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// RXF-Eval_Rpy-Cpp-ARM_V6.01 (2016-02-18).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_CFG_Highwater {
//#[ ignore
    public:
    	WST_CFG_Highwater();
    	
//#]
   
    ////    Attributes    ////

	public :
		
#if WST_INITIAL_TINY_BUFFERS > 0
		static uint16 tinyBuffersMax;		//## attribute tinyBuffersMax
#endif /* WST_INITIAL_TINY_BUFFERS */

#if WST_INITIAL_SMALL_BUFFERS > 0
		static uint16 smallBuffersMax;		//## attribute smallBuffersMax
#endif /* WST_INITIAL_SMALL_BUFFERS */
	
#if WST_INITIAL_MEDIUM_BUFFERS > 0
		static uint16 mediumBuffersMax;		//## attribute mediumBuffersMax
#endif /* WST_INITIAL_MEDIUM_BUFFERS */
	
#if WST_INITIAL_LARGE_BUFFERS > 0
		static uint16 largeBuffersMax;		//## attribute largeBuffersMax
#endif /* WST_INITIAL_LARGE_BUFFERS */
	
#if WST_INITIAL_HUGE_BUFFERS > 0
		static uint16 hugeBuffersMax;		//## attribute hugeBuffersMax
#endif /* WST_INITIAL_HUGE_BUFFERS */


	
		static uint16 timeoutsMax;		//## attribute timeoutsMax
	
		static uint16 bufferOverflow;		//## attribute bufferOverflow
};

 

#endif /* WST_CFG_Highwater_H */
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_CFG_Highwater.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
