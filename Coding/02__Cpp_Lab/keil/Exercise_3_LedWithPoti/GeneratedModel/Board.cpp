/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Board
//!	Generated Date	: Wed, 29, Mar 2017  
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
    }
    initRelations();
    initStatechart();
    //#[ operation Board(int,int)
    //#]
}

Board::Board(WST_TSK* myTask) {
    setTask( myTask, false );
    {
        {
            itsLedBar.setShouldDelete(false);
        }
    }
    initRelations();
    initStatechart();
}

Board::~Board() {
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

LedBar* Board::getItsLedBar() const {
    return (LedBar*) &itsLedBar;
}

bool Board::startBehavior() {
    bool done = true;
    done &= itsLedBar.startBehavior();
    done &= WST_FSM::startBehavior();
    return done;
}

void Board::initRelations() {
    itsLedBar._setItsBoard(this);
}

void Board::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

void Board::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        itsLedBar.setTask( myTask, false );
    }
}

void Board::destroy() {
    itsLedBar.destroy();
    WST_FSM::destroy();
}

void Board::rootState_entDef() {
    {
        rootState_subState = runLedBar;
        rootState_active = runLedBar;
        //#[ state runLedBar.(Entry) 
        CGEN ( &itsLedBar, switchLed(ledNr));
        //#]
    }
}

IOxfReactive::TakeEventStatus Board::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Board.cpp
*********************************************************************/
