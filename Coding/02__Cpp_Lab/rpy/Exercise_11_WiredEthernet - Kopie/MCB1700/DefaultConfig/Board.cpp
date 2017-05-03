/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: DefaultConfig
	Model Element	: Board
//!	Generated Date	: Wed, 26, Apr 2017  
	File Path	: MCB1700\DefaultConfig\Board.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Board.h"
//## package Default

//## class Board
Board::Board(WST_TSK* myTask) {
    setTask( myTask, false );
    {
        {
            itsLedBar.setShouldDelete(false);
        }
        {
            itsJoystick.setShouldDelete(false);
        }
    }
    initRelations();
    initStatechart();
}

Board::~Board() {
}

void Board::processJoystickData() {
    //#[ operation processJoystickData()
    switch(joystickPosition)
    {   
    	case Joystick_RIGHT: 
    			itsLedBar.toggleSingleLed(LED2_3);
    			break;  
    	case Joystick_DOWN: 
    			itsLedBar.toggleSingleLed(LED2_4);
    			break;
    	case Joystick_LEFT: 
    			itsLedBar.toggleSingleLed(LED2_5);
    			break;
    	case Joystick_UP: 
    			itsLedBar.toggleSingleLed(LED2_6);
    			break;        
    	case Joystick_SELECT: 
    			itsLedBar.onAllLeds();
    			break;
    	default: 
    			break;
    }
    //#]
}

Joystick* Board::getItsJoystick() const {
    return (Joystick*) &itsJoystick;
}

LedBar* Board::getItsLedBar() const {
    return (LedBar*) &itsLedBar;
}

bool Board::startBehavior() {
    bool done = true;
    done &= itsJoystick.startBehavior();
    done &= itsLedBar.startBehavior();
    done &= WST_FSM::startBehavior();
    return done;
}

void Board::initRelations() {
    itsJoystick._setItsBoard(this);
}

void Board::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

int Board::getJoystickPosition() const {
    return joystickPosition;
}

void Board::setJoystickPosition(int p_joystickPosition) {
    joystickPosition = p_joystickPosition;
}

void Board::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        itsLedBar.setTask( myTask, false );
        itsJoystick.setTask( myTask, false );
    }
}

void Board::destroy() {
    itsJoystick.destroy();
    itsLedBar.destroy();
    WST_FSM::destroy();
}

void Board::rootState_entDef() {
    {
        rootState_subState = Idle;
        rootState_active = Idle;
    }
}

IOxfReactive::TakeEventStatus Board::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Idle
        case Idle:
        {
            if(IS_EVENT_TYPE_OF(evNewJoystickPosition_Default_id))
                {
                    OMSETPARAMS(evNewJoystickPosition);
                    //#[ transition 0 
                    joystickPosition = params->joystickPosition;
                    //#]
                    pushNullTransition();
                    rootState_subState = ProcessJoystickData;
                    rootState_active = ProcessJoystickData;
                    //#[ state ProcessJoystickData.(Entry) 
                    processJoystickData();
                    //#]
                    res = eventConsumed;
                }
            
        }
        break;
        // State ProcessJoystickData
        case ProcessJoystickData:
        {
            if(IS_EVENT_TYPE_OF(WST_EVT_null_id ))
                {
                    popNullTransition();
                    rootState_subState = Idle;
                    rootState_active = Idle;
                    res = eventConsumed;
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}

/*********************************************************************
	File Path	: MCB1700\DefaultConfig\Board.cpp
*********************************************************************/
