#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_RXF
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_RXF.h
*********************************************************************/

#ifndef WST_RXF_H
#define WST_RXF_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]

//## package RXF::RXF_CorePkg

//## class WST_RXF
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_RXF is kind of the heart of the RXF, with it's main event based scheduling routine execute().
// 
// $Id: WST_RXF.h 32757 2015-07-24 15:49:31Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_RXF.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// RXF-Eval_Rpy-Cpp-ARM_V6.01 (2016-02-18).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.
class WST_RXF {
    ////    Constructors and destructors    ////
    
public :

    //## operation WST_RXF()
    WST_RXF( void );
    
    //## operation ~WST_RXF()
    ~WST_RXF( void );
    
    ////    Operations    ////
    
    //## operation initialize()
    static WSTBoolean initialize( void );
    
    //## operation start()
    static void start( void );

	
};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_RXF.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
