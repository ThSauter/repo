/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: LedBar
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\LedBar.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "LedBar.h"
//## package DefaultPkg

//## class LedBar
LedBar::LedBar(WST_TSK* myTask) {
    setTask( myTask, false );
    {
        for (int i = 0; i < 4; i++) 
            {
                itsLeds[i].setShouldDelete(false);
            }
        
    }
    initStatechart();
    //#[ operation LedBar()
    int i;                 
    
    // Assign the bit numbers to the leds
    for (i = 0; i < 4; i++)
    {
    	itsLeds[i].setBitIndicator(i + 3);
    }
    this->setOwner( this );
    WSTMonitor_sendInit( this, 105, (void*)&joystickPosition);
    
    //#]
}

LedBar::~LedBar() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void LedBar::offSingleLed(int ledNr) {
    //#[ operation offSingleLed(int)
    itsLeds[ledNr].off();
    //#]
}

void LedBar::onSingleLed(int ledNr) {
    //#[ operation onSingleLed(int)
    itsLeds[ledNr].on();
    //#]
}

void LedBar::processJoystickPosition() {
    //#[ operation processJoystickPosition()
    switch(joystickPosition)
    {
     	case Joystick_LEFT: 
     		toggleSingleLed(0); 
     		break;
     	case Joystick_UP: 
     		toggleSingleLed(1); 
     		break;
     	case Joystick_RIGHT: 
     		toggleSingleLed(2); 
     		break;
     	case Joystick_DOWN: 
     		toggleSingleLed(3);
     		break;
     	case Joystick_CENTER: 
     		//TODO
     		break;
     	default:
     		break; 
    }
    //#]
}

void LedBar::toggleSingleLed(int ledNr) {
    //#[ operation toggleSingleLed(int)
    FIRE( &itsLeds[ledNr], evToggle());
    
    //#]
}

int LedBar::getItsLeds() const {
    int iter = 0;
    return iter;
}

bool LedBar::startBehavior() {
    bool done = true;
    {
        int iter = 0;
        while (iter < 4){
            done &= (((Led*)&itsLeds[iter]))->startBehavior();
            iter++;
        }
    }
    done &= WST_FSM::startBehavior();
    return done;
}

void LedBar::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

char LedBar::getJoystickPosition() const {
    return joystickPosition;
}

void LedBar::setJoystickPosition(char p_joystickPosition) {
    joystickPosition = p_joystickPosition;
}

void LedBar::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        for (int i = 0; i < 4; i++) 
            {
                itsLeds[i].setTask( myTask, false );
            }
        
    }
}

void LedBar::destroy() {
    {
        int iter = 0;
        while (iter < 4){
            (((Led*)&itsLeds[iter]))->destroy();
            iter++;
        }
    }
    WST_FSM::destroy();
}

void LedBar::rootState_entDef() {
    {
        rootState_subState = Idle;
        rootState_active = Idle;
    }
}

IOxfReactive::TakeEventStatus LedBar::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Idle
        case Idle:
        {
            if(IS_EVENT_TYPE_OF(evReceivedData_DefaultPkg_id))
                {
                    OMSETPARAMS(evReceivedData);
                    //#[ transition 0 
                    joystickPosition = params->data;
                    //#]
                    pushNullTransition();
                    rootState_subState = ProcessLeds;
                    rootState_active = ProcessLeds;
                    //#[ state ProcessLeds.(Entry) 
                    processJoystickPosition();
                    //#]
                    res = eventConsumed;
                }
            
        }
        break;
        // State ProcessLeds
        case ProcessLeds:
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
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\LedBar.cpp
*********************************************************************/
