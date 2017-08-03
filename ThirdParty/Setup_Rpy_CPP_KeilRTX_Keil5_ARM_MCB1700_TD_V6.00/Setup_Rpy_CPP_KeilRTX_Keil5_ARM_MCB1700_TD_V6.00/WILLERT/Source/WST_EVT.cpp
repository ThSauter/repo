/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_EVT
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_EVT.cpp
*********************************************************************/

//## auto_generated
#include "WST_EVT.h"
//## operation toBeCancelled(WST_FSM,WST_EVT_ID_t)
#include "WST_FSM.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg

//## class WST_EVT

WSTBoolean WST_EVT::toBeCancelled(WST_FSM* dest, const WST_EVT_ID_t evtId) {
    //#[ operation toBeCancelled(WST_FSM,WST_EVT_ID_t)
    WSTBoolean returnValue = FALSE;
    if( this->destination == dest && ( this->id == evtId || evtId == 0 ) ){
    	returnValue = TRUE;
    }
    return returnValue;
    //#]
}

WST_INLINE_OP void WST_EVT::cleanUpRelations( void ) {
     destination = NULL;
}

/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_EVT.cpp
*********************************************************************/
