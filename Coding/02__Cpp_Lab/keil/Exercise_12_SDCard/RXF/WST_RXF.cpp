/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_RXF
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_RXF.cpp
*********************************************************************/

//## auto_generated
#include "WST_RXF.h"
//## auto_generated
#include "WST.h"

//## auto_generated
#include "WSTMonitor.h"
//## package RXF::RXF_CorePkg

//## class WST_RXF
WST_RXF::WST_RXF( void ) {
    //#[ operation WST_RXF()
    //#]
}

WST_RXF::~WST_RXF( void ) {
    //#[ operation ~WST_RXF()
    //#]
}

WSTBoolean WST_RXF::initialize( void ) {
    //#[ operation initialize()

    #ifdef WST_TARGET_DEBUGGING_ENABLED    
    	WSTMonitor_init();    
    #endif /* WST_TARGET_DEBUGGING_ENABLED */

    return WSTTRUE;
    //#]
}

void WST_RXF::start( void ) {
    //#[ operation start()
    theMainTask.execute();
    //#]
}

/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_RXF.cpp
*********************************************************************/
