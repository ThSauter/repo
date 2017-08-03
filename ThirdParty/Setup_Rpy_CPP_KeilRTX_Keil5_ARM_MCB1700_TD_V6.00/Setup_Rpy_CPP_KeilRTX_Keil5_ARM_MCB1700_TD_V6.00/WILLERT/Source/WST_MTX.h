#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MTX
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MTX.h
*********************************************************************/

#ifndef WST_MTX_H
#define WST_MTX_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_BehaviorPkg

//## class WST_MTX
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_MTX includes mutex functionality.
// 
// $Id: WST_MTX.h 32757 2015-07-24 15:49:31Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/RXF/RXF/Source/CPP/WST_MTX.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00 (2016-04-22).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_MTX {
    ////    Constructors and destructors    ////
    
public :

    //## operation WST_MTX()
    WST_MTX( );
    
    //## operation WST_MTX()
    WST_MTX( const WST_MTX* mtx );
    
    //## operation ~WST_MTX()
    ~WST_MTX( void );
    
    ////    Operations    ////
    
    //## operation WST_MTX_enterCriticalRegion()
    void WST_MTX_enterCriticalRegion( void );
    
    //## operation WST_MTX_exitCriticalRegion()
    void WST_MTX_exitCriticalRegion( void );
    
    WST_RTOS_MTX_t *WST_MTX_getRtosMutex( void );

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
     ////    Attributes    ////
    WST_RTOS_MTX_t rtosMutex;		//## attribute rtosMutex
    
    WST_MTX *mtx;
};

class WST_MTX_inUse {

public:

    //## operation WST_MTX()
	WST_MTX_inUse( const WST_MTX* mtx );

    //## operation ~WST_MTX()
    ~WST_MTX_inUse( void );

private:
    WST_MTX myMutex;
};


#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MTX.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
