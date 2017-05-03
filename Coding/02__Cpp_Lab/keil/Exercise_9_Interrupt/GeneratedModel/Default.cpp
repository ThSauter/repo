/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Fri, 7, Apr 2017  
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/

//## auto_generated
#include "Default.h"
//## classInstance itsBoard
#include "Board.h"
//## auto_generated
#include "Display.h"
//## auto_generated
#include "Interrupt.h"
//## auto_generated
#include "LedBar.h"
//## auto_generated
#include "Poti.h"
//## package Default


//## classInstance itsBoard
Board itsBoard(1000,2);

//## operation EINT0_IRQHandler()
extern "C" void EINT0_IRQHandler() {
    //#[ operation EINT0_IRQHandler()
    // Clear EINT0 interrupt (page 24)
    LPC_SC->EXTINT |= (1<<0); 
    
    itsBoard.GEN(evExtInterrupt());
    
    //#]
}

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

//## event evPotiValue(int)
evPotiValue::evPotiValue(int p_potiValue) : potiValue(p_potiValue) {
    setId(evPotiValue_Default_id);
}

bool evPotiValue::isTypeOf(WST_EVT_ID_t id) const {
    return (evPotiValue_Default_id==id);
}

//## event evExtInterrupt()
evExtInterrupt::evExtInterrupt() {
    setId(evExtInterrupt_Default_id);
}

bool evExtInterrupt::isTypeOf(WST_EVT_ID_t id) const {
    return (evExtInterrupt_Default_id==id);
}

/*********************************************************************
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/
