/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Mon, 24, Apr 2017  
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/

//## auto_generated
#include "Default.h"
//## classInstance itsBoard
#include "Board.h"
//## auto_generated
#include "Joystick.h"
//## auto_generated
#include "Led.h"
//## auto_generated
#include "LedBar.h"
//## package Default


//## classInstance itsBoard
Board itsBoard;

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

//## event evNewJoystickPosition(int)
evNewJoystickPosition::evNewJoystickPosition(int p_joystickPosition) : joystickPosition(p_joystickPosition) {
    setId(evNewJoystickPosition_Default_id);
}

bool evNewJoystickPosition::isTypeOf(WST_EVT_ID_t id) const {
    return (evNewJoystickPosition_Default_id==id);
}

//## event evToggleLed()
evToggleLed::evToggleLed() {
    setId(evToggleLed_Default_id);
}

bool evToggleLed::isTypeOf(WST_EVT_ID_t id) const {
    return (evToggleLed_Default_id==id);
}

/*********************************************************************
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/
