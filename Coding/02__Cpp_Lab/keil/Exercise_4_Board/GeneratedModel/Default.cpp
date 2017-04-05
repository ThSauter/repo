/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Fri, 31, Mar 2017  
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/

//## auto_generated
#include "Default.h"
//## classInstance itsBoard
#include "Board.h"
//## auto_generated
#include "LedBar.h"
//## package Default


//## classInstance itsBoard
Board itsBoard(1000,2);

void Default_initRelations() {
    {
        {
            itsBoard.setShouldDelete(false);
        }
    }
}

bool Default_startBehavior() {
    bool done = true;
    done &= itsBoard.startBehavior();
    return done;
}

//#[ ignore
Default_OMInitializer::Default_OMInitializer() {
    Default_initRelations();
    Default_startBehavior();
}

Default_OMInitializer::~Default_OMInitializer() {
}
//#]

//## event evSwitchLed(int)
evSwitchLed::evSwitchLed(int p_ledNr) : ledNr(p_ledNr) {
    setId(evSwitchLed_Default_id);
}

bool evSwitchLed::isTypeOf(WST_EVT_ID_t id) const {
    return (evSwitchLed_Default_id==id);
}

/*********************************************************************
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/
