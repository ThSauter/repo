/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Board
//!	Generated Date	: Wed, 5, Apr 2017  
	File Path	: MCB1700\Debug\Board.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Board.h"
//## package Default

//## class Board
Board::Board(int aDelay, int aLedNr, WST_TSK* myTask) {
    setTask( myTask, false );
    {
        {
            itsLedBar.setShouldDelete(false);
        }
        {
            itsPoti.setShouldDelete(false);
        }
        {
            itsDisplay.setShouldDelete(false);
        }
        {
            itsJoystick.setShouldDelete(false);
        }
    }
    initRelations();
    initStatechart();
    //#[ operation Board(int,int)
    delay = aDelay;
    ledNr = aLedNr;
    //#]
}

Board::Board(WST_TSK* myTask) {
    setTask( myTask, false );
    {
        {
            itsLedBar.setShouldDelete(false);
        }
        {
            itsPoti.setShouldDelete(false);
        }
        {
            itsDisplay.setShouldDelete(false);
        }
        {
            itsJoystick.setShouldDelete(false);
        }
    }
    initRelations();
    initStatechart();
}

Board::~Board() {
    cancelTimeouts();
}

void Board::drawPotiValue(int potiValue) {
    //#[ operation drawPotiValue(int)
    char str[20];  
    sprintf(str, "Poti Value: %i", potiValue); 
    itsDisplay.drawString(5,40,str);   
    //#]
}

int Board::getDelay() const {
    return delay;
}

void Board::setDelay(int p_delay) {
    delay = p_delay;
}

int Board::getJoystickPos() const {
    return joystickPos;
}

void Board::setJoystickPos(int p_joystickPos) {
    joystickPos = p_joystickPos;
}

int Board::getLedNr() const {
    return ledNr;
}

void Board::setLedNr(int p_ledNr) {
    ledNr = p_ledNr;
}

int Board::getPotiValue() const {
    return potiValue;
}

void Board::setPotiValue(int p_potiValue) {
    potiValue = p_potiValue;
}

Display* Board::getItsDisplay() const {
    return (Display*) &itsDisplay;
}

Joystick* Board::getItsJoystick() const {
    return (Joystick*) &itsJoystick;
}

LedBar* Board::getItsLedBar() const {
    return (LedBar*) &itsLedBar;
}

Poti* Board::getItsPoti() const {
    return (Poti*) &itsPoti;
}

bool Board::startBehavior() {
    bool done = true;
    done &= itsDisplay.startBehavior();
    done &= itsJoystick.startBehavior();
    done &= itsLedBar.startBehavior();
    done &= itsPoti.startBehavior();
    done &= WST_FSM::startBehavior();
    return done;
}

void Board::initRelations() {
    itsDisplay._setItsBoard(this);
    itsJoystick._setItsBoard(this);
    itsLedBar._setItsBoard(this);
    itsPoti._setItsBoard(this);
}

void Board::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    state_4_subState = OMNonState;
    state_4_active = OMNonState;
    state_3_subState = OMNonState;
    state_3_active = OMNonState;
    runLedBar_subState = OMNonState;
    runLedBar_timeout = NULL;
    state_3_timeout = NULL;
}

void Board::cancelTimeouts() {
    cancel(runLedBar_timeout);
    cancel(state_3_timeout);
}

bool Board::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(runLedBar_timeout == arg)
        {
            runLedBar_timeout = NULL;
            res = true;
        }
    if(state_3_timeout == arg)
        {
            state_3_timeout = NULL;
            res = true;
        }
    return res;
}

void Board::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        itsLedBar.setTask( myTask, false );
        itsPoti.setTask( myTask, false );
        itsDisplay.setTask( myTask, false );
        itsJoystick.setTask( myTask, false );
    }
}

void Board::destroy() {
    itsDisplay.destroy();
    itsJoystick.destroy();
    itsLedBar.destroy();
    itsPoti.destroy();
    WST_FSM::destroy();
}

void Board::rootState_entDef() {
    {
        state_2_entDef();
    }
}

IOxfReactive::TakeEventStatus Board::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State state_2
    if(rootState_active == state_2)
        {
            res = state_2_processEvent();
        }
    return res;
}

void Board::state_2_entDef() {
    rootState_subState = state_2;
    rootState_active = state_2;
    state_3_entDef();
    state_4_entDef();
}

void Board::state_2_exit() {
    switch (state_3_subState) {
        // State runLedBar
        case runLedBar:
        {
            runLedBar_exit();
        }
        break;
        // State pauseLedBar
        case pauseLedBar:
        {
            cancel(state_3_timeout);
        }
        break;
        default:
            break;
    }
    state_3_subState = OMNonState;
    // State updateDisplay
    
    state_4_subState = OMNonState;
    
}

IOxfReactive::TakeEventStatus Board::state_2_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State state_3
    if(state_3_processEvent() != eventNotConsumed)
        {
            res = eventConsumed;
            if(!IS_IN(state_2))
                {
                    return res;
                }
        }
    // State state_4
    if(state_4_processEvent() != eventNotConsumed)
        {
            res = eventConsumed;
            if(!IS_IN(state_2))
                {
                    return res;
                }
        }
    
    return res;
}

void Board::state_4_entDef() {
    
    state_4_subState = updateDisplay;
    state_4_active = updateDisplay;
    //#[ state state_2.state_4.updateDisplay.(Entry) 
    drawPotiValue(potiValue);
    delay = potiValue;
    //#]
}

IOxfReactive::TakeEventStatus Board::state_4_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State updateDisplay
    if(state_4_active == updateDisplay)
        {
            if(IS_EVENT_TYPE_OF(evPotiValue_Default_id))
                {
                    OMSETPARAMS(evPotiValue);
                    //#[ transition 5 
                    potiValue = params->potiValue;
                    //#]
                    state_4_subState = updateDisplay;
                    state_4_active = updateDisplay;
                    //#[ state state_2.state_4.updateDisplay.(Entry) 
                    drawPotiValue(potiValue);
                    delay = potiValue;
                    //#]
                    res = eventConsumed;
                }
            
            
        }
    return res;
}

void Board::state_3_entDef() {
    
    runLedBar_entDef();
}

IOxfReactive::TakeEventStatus Board::state_3_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (state_3_active) {
        // State notifyLedBar
        case notifyLedBar:
        {
            res = notifyLedBar_handleEvent();
        }
        break;
        // State pauseLedBar
        case pauseLedBar:
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == state_3_timeout)
                        {
                            cancel(state_3_timeout);
                            runLedBar_entDef();
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

void Board::runLedBar_entDef() {
    state_3_subState = runLedBar;
    runLedBar_subState = notifyLedBar;
    state_3_active = notifyLedBar;
    runLedBar_timeout = scheduleTimeout(delay, NULL);
}

void Board::runLedBar_exit() {
    // State notifyLedBar
    if(runLedBar_subState == notifyLedBar)
        {
            cancel(runLedBar_timeout);
            //#[ state state_2.state_3.runLedBar.notifyLedBar.(Exit) 
            CGEN ( &itsLedBar, evSwitchLed(ledNr));    
            
            //#]
        }
    runLedBar_subState = OMNonState;
    
}

IOxfReactive::TakeEventStatus Board::runLedBar_handleEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    if(IS_EVENT_TYPE_OF(evJoystickLeft_Default_id))
        {
            runLedBar_exit();
            state_3_subState = pauseLedBar;
            state_3_active = pauseLedBar;
            state_3_timeout = scheduleTimeout(5000, NULL);
            res = eventConsumed;
        }
    
    
    return res;
}

IOxfReactive::TakeEventStatus Board::notifyLedBar_handleEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    if(IS_EVENT_TYPE_OF(WST_TMR_id))
        {
            if(getCurrentEvent() == runLedBar_timeout)
                {
                    //## transition 3 
                    if(ledNr == 6)
                        {
                            cancel(runLedBar_timeout);
                            //#[ state state_2.state_3.runLedBar.notifyLedBar.(Exit) 
                            CGEN ( &itsLedBar, evSwitchLed(ledNr));    
                            
                            //#]
                            //#[ transition 3 
                            ledNr = 2;
                            //#]
                            runLedBar_subState = notifyLedBar;
                            state_3_active = notifyLedBar;
                            runLedBar_timeout = scheduleTimeout(delay, NULL);
                            res = eventConsumed;
                        }
                    else
                        {
                            cancel(runLedBar_timeout);
                            //#[ state state_2.state_3.runLedBar.notifyLedBar.(Exit) 
                            CGEN ( &itsLedBar, evSwitchLed(ledNr));    
                            
                            //#]
                            //#[ transition 2 
                            ledNr++;
                            //#]
                            runLedBar_subState = notifyLedBar;
                            state_3_active = notifyLedBar;
                            runLedBar_timeout = scheduleTimeout(delay, NULL);
                            res = eventConsumed;
                        }
                }
        }
    
    if(res == eventNotConsumed)
        {
            res = runLedBar_handleEvent();
        }
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Board.cpp
*********************************************************************/
