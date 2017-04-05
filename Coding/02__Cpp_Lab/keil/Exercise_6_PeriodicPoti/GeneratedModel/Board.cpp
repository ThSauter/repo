/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Board
//!	Generated Date	: Mon, 3, Apr 2017  
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

LedBar* Board::getItsLedBar() const {
    return (LedBar*) &itsLedBar;
}

Poti* Board::getItsPoti() const {
    return (Poti*) &itsPoti;
}

bool Board::startBehavior() {
    bool done = true;
    done &= itsDisplay.startBehavior();
    done &= itsLedBar.startBehavior();
    done &= itsPoti.startBehavior();
    done &= WST_FSM::startBehavior();
    return done;
}

void Board::initRelations() {
    itsDisplay._setItsBoard(this);
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
    state_3_timeout = NULL;
}

void Board::cancelTimeouts() {
    cancel(state_3_timeout);
}

bool Board::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
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
    }
}

void Board::destroy() {
    itsDisplay.destroy();
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
    state_3_exit();
    // State updateDisplay
    if(state_4_subState == updateDisplay)
        {
            //#[ state state_2.state_4.updateDisplay.(Exit) 
            delay = potiValue;
            //#]
        }
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
                    //#[ state state_2.state_4.updateDisplay.(Exit) 
                    delay = potiValue;
                    //#]
                    //#[ transition 5 
                    potiValue = params->potiValue;
                    //#]
                    state_4_subState = updateDisplay;
                    state_4_active = updateDisplay;
                    //#[ state state_2.state_4.updateDisplay.(Entry) 
                    drawPotiValue(potiValue);
                    
                    //#]
                    res = eventConsumed;
                }
            
            
        }
    return res;
}

void Board::state_3_entDef() {
    
    state_3_subState = runLedBar;
    state_3_active = runLedBar;
    state_3_timeout = scheduleTimeout(delay, NULL);
}

void Board::state_3_exit() {
    // State runLedBar
    if(state_3_subState == runLedBar)
        {
            cancel(state_3_timeout);
            //#[ state state_2.state_3.runLedBar.(Exit) 
            CGEN ( &itsLedBar, evSwitchLed(ledNr));
            //#]
        }
    state_3_subState = OMNonState;
    
}

IOxfReactive::TakeEventStatus Board::state_3_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State runLedBar
    if(state_3_active == runLedBar)
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == state_3_timeout)
                        {
                            //## transition 3 
                            if(ledNr == 6)
                                {
                                    cancel(state_3_timeout);
                                    //#[ state state_2.state_3.runLedBar.(Exit) 
                                    CGEN ( &itsLedBar, evSwitchLed(ledNr));
                                    //#]
                                    //#[ transition 3 
                                    ledNr = 2;
                                    //#]
                                    state_3_subState = runLedBar;
                                    state_3_active = runLedBar;
                                    state_3_timeout = scheduleTimeout(delay, NULL);
                                    res = eventConsumed;
                                }
                            else
                                {
                                    cancel(state_3_timeout);
                                    //#[ state state_2.state_3.runLedBar.(Exit) 
                                    CGEN ( &itsLedBar, evSwitchLed(ledNr));
                                    //#]
                                    //#[ transition 2 
                                    ledNr++;
                                    //#]
                                    state_3_subState = runLedBar;
                                    state_3_active = runLedBar;
                                    state_3_timeout = scheduleTimeout(delay, NULL);
                                    res = eventConsumed;
                                }
                        }
                }
            
            
        }
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Board.cpp
*********************************************************************/
