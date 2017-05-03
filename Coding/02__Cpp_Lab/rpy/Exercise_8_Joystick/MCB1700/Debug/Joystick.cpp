/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Joystick
//!	Generated Date	: Wed, 5, Apr 2017  
	File Path	: MCB1700\Debug\Joystick.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Joystick.h"
//## link itsBoard
#include "Board.h"
//## package Default

//## class Joystick
Joystick::Joystick(WST_TSK* myTask) {
    setTask( myTask, false );
    itsBoard = NULL;
    initStatechart();
    //#[ operation Joystick()
    LPC_GPIO1->FIODIR&= ~((1UL<<20)|(1UL<<23)|
    (1UL<<24)| (1UL<<25)| (1UL<<26));
    /* Port P1.20 and 1.23 to 1.26 is input (Joystick)*/
    //#]
}

Joystick::~Joystick() {
    cleanUpRelations();
    cancelTimeouts();
}

void Joystick::sample() {
    //#[ operation sample()
    int position = (LPC_GPIO1->FIOPIN >> 20) & Joystick_Mask ;
    // last 7 Bits now are related to Joystick
    
    position = position >> 3; 
    
    if (lastPosition != position)
    {
    	lastPosition = position;    
    	
    	switch (lastPosition)
    	{
    		case Joystick_LEFT: CGEN( itsBoard, evJoystickLeft()); 
    	}
    }   
    
    
    //#]
}

Board* Joystick::getItsBoard() const {
    return itsBoard;
}

void Joystick::setItsBoard(Board* p_Board) {
    _setItsBoard(p_Board);
}

bool Joystick::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    return done;
}

void Joystick::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void Joystick::cleanUpRelations() {
    if(itsBoard != NULL)
        {
            itsBoard = NULL;
        }
}

void Joystick::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool Joystick::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

int Joystick::getLastPosition() const {
    return lastPosition;
}

void Joystick::setLastPosition(int p_lastPosition) {
    lastPosition = p_lastPosition;
}

void Joystick::__setItsBoard(Board* p_Board) {
    itsBoard = p_Board;
}

void Joystick::_setItsBoard(Board* p_Board) {
    __setItsBoard(p_Board);
}

void Joystick::_clearItsBoard() {
    itsBoard = NULL;
}

void Joystick::rootState_entDef() {
    {
        pushNullTransition();
        rootState_subState = Sample;
        rootState_active = Sample;
        //#[ state Sample.(Entry) 
        sample();
        //#]
    }
}

IOxfReactive::TakeEventStatus Joystick::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Sample
        case Sample:
        {
            if(IS_EVENT_TYPE_OF(WST_EVT_null_id ))
                {
                    popNullTransition();
                    rootState_subState = Hold;
                    rootState_active = Hold;
                    rootState_timeout = scheduleTimeout(100, NULL);
                    res = eventConsumed;
                }
            
        }
        break;
        // State Hold
        case Hold:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            pushNullTransition();
                            rootState_subState = Sample;
                            rootState_active = Sample;
                            //#[ state Sample.(Entry) 
                            sample();
                            //#]
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Joystick.cpp
*********************************************************************/
